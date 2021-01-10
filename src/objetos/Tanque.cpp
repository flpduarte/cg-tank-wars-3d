//
// Created by Felipe on 07/01/2021.
//

#include <objetos/Tanque.h>
#include <objetos/jogador.hpp>
#include <graphics/cor.h>
#include <auxiliar/auxiliares.hpp>
#include <cmath>
#include <objetos3D.hpp>
#include <objetos/explosoes.hpp>

Tanque::Tanque(Jogador &jogador) : jogador(jogador) {
    cor::definir_cor(this->corAtual, jogador.corBase);
    this->posicao[0] = 0;
    this->posicao[1] = 0;
    this->posicao[2] = 0;
    this->vetorNormal[0] = 0;
    this->vetorNormal[1] = 0;
    this->vetorNormal[2] = 1;

    // Restaura as propriedades iniciais do tanque
    this->vivo     = true;
    this->homens   = 100;
    this->anguloCanhao   = 90;
    this->potencia = 200;

    // Define um novo tipo de morte para a rodada
    tipo_morte      = rand() % NUM_TIPOS_MORTE;
    variacao_morte  = rand() % NUM_VARIACOES_MORTE[tipo_morte];
    frame           = 0;
    animacaoFinalizada = false;
}

bool Tanque::isVivo() const {
    return vivo;
}

const std::string &Tanque::getNome() const {
    return jogador.nome;
}

/**
 * Retorna o ângulo do tanque em formato de string, para ser exibido na tela.
 * Formato:
 * [0, 90]: "45 >"      Sinal de maior indica a direção - direita
 *
 * (90, 180]: "45 <"    Sinal de menor indica a direção - esquerda
 */
std::string Tanque::getAnguloEmString() const
{
    return anguloCanhao > 90 ? std::to_string(180 - anguloCanhao) + " <" : std::to_string(anguloCanhao) + " >";
}

int Tanque::getPotencia() const {
    return potencia;
}

int Tanque::getNumeroDeHomens() const {
    return homens;
}

/**
 * Retorna a corBase "real" do tanque - homens/100 * corBase.
 */
float *Tanque::getCorReal()
{
    // altera só as componentes RGB. Componente A permanece = 1.
    for (int i = 0; i < 3; i++)
    {
        corAtual[i] = jogador.corBase[i] * homens / 100.;
    }
    return corAtual;
}

double *Tanque::getPosicao() {
    return posicao;
}

bool Tanque::isAnimacaoFinalizada() const {
    return animacaoFinalizada;
}


void Tanque::setAnguloPara75Direita() {
    anguloCanhao = 75;
}

void Tanque::setAnguloPara75Esquerda() {
    anguloCanhao = 105;
}

void Tanque::incrementarAnguloSentidoHorario() {
    anguloCanhao++;
    if (anguloCanhao > 180) {
        anguloCanhao = 0;
    }
}

void Tanque::incrementarAnguloSentidoAntiHorario() {
    anguloCanhao--;
    if (anguloCanhao < 0) {
        anguloCanhao = 180;
    }
}

void Tanque::aumentarPotenciaLento() {
    if (potencia < POTENCIA_MAXIMA) {
        potencia++;
    }
}

void Tanque::aumentarPotenciaRapido() {
    potencia += 100;
    if (potencia > POTENCIA_MAXIMA) {
        potencia = POTENCIA_MAXIMA;
    }
}

void Tanque::diminuirPotenciaLento() {
    if (potencia > 0) {
        potencia--;
    }
}

void Tanque::diminuirPotenciaRapido() {
    potencia -= 100;
    if (potencia < 0) {
        potencia = 0;
    }
}

const std::string &Tanque::getNomeDaArmaAtual() const {
    return jogador.lista_armas->arma_atual()->nome;
}

void Tanque::selecionarProximaArma() const {
    jogador.lista_armas->selecionar_proxima();
}

/**
 * Desenha o tanque correspondente ao jogador.
 * Utiliza o estado atual do objeto para posicioná-lo. Objeto tanque possuirá
 * atualizados: coordenadas (x, y, z) e o vetor vetorNormal do terreno no local onde
 * o tanque se situa.
 *
 * Assume que a matriz ativa é a MODELVIEW.
 * Assume que vetorNormal já está normalizado (módulo = 1). É válido, desde que tenha
 * sido obtido a partir da matriz de vetores normais do cenário.
 */
void Tanque::desenhar()
{
    // Calcula o vetor eixo de rotação do tanque
    const double cima[3] = {0, 0, 1};
    double eixo[3] = {0};
    aux::prod_vetorial(cima, vetorNormal, eixo);
    double anguloCorpoDoTanque = acos(aux::prod_escalar(cima, vetorNormal)) * 180 / M_PI;

    // Translada o tanque para a sua posição no mundo
    glPushMatrix();
    glTranslated(posicao[0], posicao[1], posicao[2]);
    glScaled(TAMANHO_TANQUE, TAMANHO_TANQUE, TAMANHO_TANQUE);

    // Rotaciona o tanque e o desenha
    glPushMatrix();
    glRotated(anguloCorpoDoTanque, eixo[0], eixo[1], eixo[2]);
    desenhar_tanque(this->getCorReal());                  // em Objetos3D
    glPopMatrix();

    // Prepara para desenhar o canhão: translada centro dos eixos para a esfera
    glTranslated(.75 / 4 * vetorNormal[0], .75 / 4 * vetorNormal[1], .75 / 4 * vetorNormal[2]);

    // Gira os eixos para o eixo X do canhão apontar para o ângulo certo
    glRotated(this->anguloCanhao, 0, -1, 0);
    desenhar_canhao();                                      // em Objetos3D

    // Desempilhar a matriz
    glPopMatrix();
}

/**
 * Atalhos para atualizar posição e inclinação do tanque
 */
void Tanque::posicionar(const double nova_pos[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->posicao[i] = nova_pos[i];
    }
}
void Tanque::definir_normal(const GLfloat normal[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->vetorNormal[i] = normal[i];
    }
}

/**
 * preparar_para_jogar():
 * Realiza alguns ajustes menores do jogador antes de iniciar a sua vez:
 * - Muda de armamento, caso a munição da arma atual seja = 0;
 * - Muda potência para o máximo possível, caso o jogador tenha
 *   sofrido dano, e a sua última potência selecionada supere a
 *   potência máxima.
 */
void Tanque::preparar_para_jogar()
{
    jogador.preparar_para_jogar();

    // Muda potência, se necessário
    if (potencia > homens*10)
    {
        potencia = homens*10;
    }
}

/**
 * atirar()
 * Lança um projétil a partir do tanque atual. É chamado pelo Cenário.
 * O projétil é criado na ponta do canhão do tanque, com velocidade inicial
 * dada pela multiplicação da potência pelo fator constante POT_PARA_VEL.
 *
 * Entrada: Objeto Cenario, no qual o tanque está localizado; é repassado ao Projetil.
 */
Projetil *Tanque::atirar(Cenario *cenario) const
{
    // Definir posição inicial do projétil
    double ang_rad   = anguloCanhao * M_PI / 180.;
    double V0 = FATOR_POT_VEL * potencia;
    double X0[6] = {0};
    X0[0] = posicao[0] + TAMANHO_TANQUE * (vetorNormal[0] * .75 / 2 + COMPR_CANHAO * cos(ang_rad));
    X0[1] = posicao[1];
    X0[2] = posicao[2] + TAMANHO_TANQUE * (vetorNormal[2] * .75 / 2 + COMPR_CANHAO * sin(ang_rad));

    // Calcular velocidade inicial do projétil
    X0[3] = V0 * cos(ang_rad);
    X0[4] = 0;
    X0[5] = V0 * sin(ang_rad);

    // definir vetor velocidade inicial
    return new Projetil(jogador.atirarArmaAtual(), cenario, X0);
}


/**
 * atingiu(): retorna true se a posição dada está localizado dentro
 * do hitbox do tanque.
 *
 * Vetor X deve ter 3 posições: (x, y, z).
 */
bool Tanque::atingiu(const double *X) const {
    // Se o jogador não estiver vivo, nem realiza nenhum cálculo.
    if (!vivo)
        return false;

        // Para ser mais preciso, seria necessário calcular se o projétil
        // atingiu alguma parte do tanque.
        // Por simplicidade, considerou-se que o tanque possui formato
        // esférico, com raio = 3/4 de seu comprimento. Esse é o chamado
        // "hitbox" do tanque.
    else
        return ((posicao[0] - X[0]) * (posicao[0] - X[0]) +
                (posicao[1] - X[1]) * (posicao[1] - X[1]) +
                (posicao[2] - X[2]) * (posicao[2] - X[2]))
               < (HITBOX_TANQUE*HITBOX_TANQUE);
}

/**
 * Exibe os frames de morte do tanque.
 */
void Tanque::morte_proximo_frame()
{
    // Realizar animação conforme tipo de morte.
    switch (tipo_morte)
    {
        case MELTDOWN:
            meltdown();
            break;
    }
}

/**
 * meltdown(): Imita a morte do tipo "Meltdown" do Tank Wars original.
 * A ideia é fazer o tanque aumentar o brilho até 100% em 100 frames,
 * em seguida diminuir o brilho de volta pra 0 nos próximos 100 frames.
 *
 */
void Tanque::meltdown()
{
    // TODO: Transformar a animação abaixo em uma subclasse de uma classe maior de explosão.
    // TODO: Transformar a classe "Explosao" original em outra subclasse da classe de explosões.
    //assert(animacaoFinalizada == false);

    // variacao 0: não explode.
    if (variacao_morte == 0)
    {
        if (frame < frame_interv_meltdown)
        {
            this->homens = (int) ((double)frame/frame_interv_meltdown * 100.); // incrementa, depois usa o frame
        }
        else if (frame < 2*frame_interv_meltdown)
        {
            this->homens = (int) ( 100. * (1 - (double)(frame - frame_interv_meltdown)/frame_interv_meltdown ));
        }

            // Finalizar animação
        else
        {
            this->homens = 0;
            this->animacaoFinalizada = true;
        }
    }

        // variacao 1-4: realiza animação e ao final cria uma explosão.
        // quanto maior a variação, maior a explosão.
    else
    {
        // Brilho do tanque antes da explosão
        if (frame < frame_interv_meltdown)
        {
            this->homens = (int) ((double)frame/frame_interv_meltdown * 100.);
        }
        else if (frame < 2*frame_interv_meltdown)
        {
            this->homens = (int) ((double)(frame - frame_interv_meltdown)/frame_interv_meltdown * 100.);
        }
        else if (frame < 3*frame_interv_meltdown)
        {
            this->homens = (int) ((double)(frame - 2*frame_interv_meltdown)/frame_interv_meltdown * 100.);
        }
        else if (frame < 4*frame_interv_meltdown)
        {
            this->homens = (int) (100. * (1. - (frame - 3.*frame_interv_meltdown)/frame_interv_meltdown ));
        }

            // cria explosão após animação.
        else
        {
            this->homens = 0;
            //mundo.cenario->criar_explosao(this->posicao, RAIO_INCINERADOR * pow(2, variacao_morte - 1));
            this->animacaoFinalizada = true;
        }
    }

    // incrementa frame
    frame++;
}

/**
 * Cria uma nova explosão após o meltdown, se houver a explosão..
 * TODO: esta função deverá ser desnecessária após converter o Meltdown em uma subclasse Explosão por si só.
 */
Explosao *Tanque::gerarExplosaoAdicional() const {
    if (animacaoFinalizada && variacao_morte > 0)
        return new Explosao(posicao, RAIO_INCINERADOR * pow(2, variacao_morte - 1));
    else
        return nullptr;
}

/**
 * Reduz homens do tanque na quantidade especificada, devido a danos sofridos pelo tanque.
 * Se o número de homens atingir zero, o tanque deixa de estar vivo (vivo = false).
 */
void Tanque::removerHomens(int quantidade) {
    homens -= quantidade;
    if (homens <= 0) {
        homens = 0;
        vivo = false;
    }
}

void Tanque::registrarVitoria() const {
    jogador.vitorias++;
}



