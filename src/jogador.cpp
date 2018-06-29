/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa os métodos da classe Jogador.
 *
 */
// para desativar asserts, ativar este comando antes de #define <cassert>
//#define NDEBUG
#include <cmath>
#include <string>
#include <iostream>
#include <ctime>
#include <cassert>
#include "jogador.hpp"
#include "globals.hpp"
#include "auxiliares.hpp"
#include "constantes.hpp"
#include "objetos3D.hpp"
#include "cenario.hpp"

void definir_cor(float *, const int);     // função local para definir a cor do tanque

/**
 * Cria um novo jogador.
 * Entrada: número do jogador: 1, 2, ..., MAX_JOGADORES.
 */
Jogador::Jogador(int i): njogador(i)
{
    // define a cor do tanque:
    definir_cor(this->cor, i);
    cor::definir_cor(this->cor_alterada, this->cor);
    this->nome = "Jogador " + std::to_string(i);
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->normal[0] = 0;
    this->normal[1] = 0;
    this->normal[2] = 1;
    this->lista_armas = new ListaArmamentos;
}

/**
 * condicao_inicial(): Restaura as configurações do jogador para a condição de
 * início de jogo:
 * - Pontos = 0
 * - Dolares = 0
 * - Armas: Apenas Incinerador, com QTD_INCINERADOR tiros
 */
void Jogador::condicao_inicial()
{
    // zera pontuação e dolares e reseta lista de armamentos
    this->vitorias = 0;
    this->pontos = 0;
    this->dolares = 0;
    this->lista_armas->condicao_inicial();
}

/**
 * Redefine o status do jogador para a condição de início de rodada:
 * - homens = 100
 * - vivo   = true
 */
void Jogador::reiniciar()
{
    // Restaura propriedades
    this->vivo     = true;
    this->homens   = 100;
    this->angulo   = 90;
    this->potencia = 200;

    // Define um novo tipo de morte para a rodada
    tipo_morte      = rand() % NUM_TIPOS_MORTE;
    variacao_morte  = rand() % NUM_VARIACOES_MORTE[tipo_morte];
    frame           = 0;
    anim_finalizada = false;
}


/**
 * Retorna o ângulo do tanque em formato de string, para ser exibido na tela.
 * Formato:
 * [0, 90]: "45 >"      Sinal de maior indica a direção - direita
 *
 * (90, 180]: "45 <"    Sinal de menor indica a direção - esquerda
 */
std::string Jogador::angulo_texto()
{
    return angulo > 90 ? std::to_string(180 - angulo) + " <" : std::to_string(angulo) + " >";
}


/**
 * Libera a memória utilizada pelo objeto Jogador
 */
Jogador::~Jogador()
{
    delete lista_armas;
}


/**
 * Retorna a cor "real" do tanque - homens/100 * cor.
 */
float *Jogador::cor_real()
{
    // altera só as componentes RGB. Componente A permanece = 1.
    for (int i = 0; i < 3; i++)
    {
        cor_alterada[i] = cor[i]*homens/100.;
    }
    return cor_alterada;
}

/**
 * Desenha o tanque correspondente ao jogador.
 * Utiliza o estado atual do objeto para posicioná-lo. Objeto tanque possuirá
 * atualizados: coordenadas (x, y, z) e o vetor normal do terreno no local onde
 * o tanque se situa.
 *
 * Assume que a matriz ativa é a MODELVIEW.
 * Assume que normal já está normalizado (módulo = 1). É válido, desde que tenha
 * sido obtido a partir da matriz de vetores normais do cenário.
 */
void Jogador::desenhar()
{
    // Calcula o vetor eixo de rotação do tanque
    const double cima[3] = {0, 0, 1};
    double eixo[3] = {0};
    aux::prod_vetorial(cima, normal, eixo);
    double angulo = acos(aux::prod_escalar(cima, normal)) * 180/PI;

    // Translada o tanque para a sua posição no mundo
    glPushMatrix();
    glTranslated(pos[0], pos[1], pos[2]);
    glScaled(TAMANHO_TANQUE, TAMANHO_TANQUE, TAMANHO_TANQUE);

    // Rotaciona o tanque e o desenha
    glPushMatrix();
    glRotated(angulo, eixo[0], eixo[1], eixo[2]);
    desenhar_tanque(this->cor_real());
    glPopMatrix();

    // Prepara para desenhar o canhão: translada centro dos eixos para a esfera
    glTranslated(.75/4*normal[0], .75/4*normal[1], .75/4*normal[2]);

    // Gira os eixos para o eixo X do canhão apontar para o ângulo certo
    glRotated(this->angulo, 0, -1, 0);
    desenhar_canhao();

    // Desempilhar a matriz
    glPopMatrix();
}

/**
 * Atalhos para atualizar posição e inclinação do tanque
 */
void Jogador::posicionar(double nova_pos[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->pos[i] = nova_pos[i];
    }
}
void Jogador::definir_normal(GLfloat normal[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->normal[i] = normal[i];
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
void Jogador::preparar_para_jogar()
{
    // Muda arma, se necessário
    if (lista_armas->qtd_atual() <= 0)
    {
        lista_armas->selecionar_proxima();
    }

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
 * Entrada: velocidade do vento, recebido do cenário.
 *
 * NOTA: ASSUME que o vetor normal é unitário!
 */
Projetil *Jogador::atirar(int vento)
{
    // Definir posição inicial do projétil
    double ang_rad   = angulo * PI/180.;
    double V0 = FATOR_POT_VEL * potencia;
    double X0[6] = {0};
    X0[0] = pos[0] + TAMANHO_TANQUE *(normal[0]*.75/2 + COMPR_CANHAO*cos(ang_rad));
    X0[1] = pos[1];
    X0[2] = pos[2] + TAMANHO_TANQUE *(normal[2]*.75/2 + COMPR_CANHAO*sin(ang_rad));

    // Calcular velocidade inicial do projétil
    X0[3] = V0 * cos(ang_rad);
    X0[4] = 0;
    X0[5] = V0 * sin(ang_rad);

    // definir vetor velocidade inicial
    return new Projetil(lista_armas->atirar_arma_atual(), X0, vento);
}


/**
 * atingiu(): retorna true se o projétil na posição dada atinge o tanque.
 * Retorna false, caso contrário.
 *
 * Assume que o vetor X tem pelo menos 3 posições: (x, y, z).
 */
bool Jogador::atingiu(double *X)
{
    // Se o jogador não estiver vivo, nem realiza nenhum cálculo.
    if (!vivo)
        return false;

    // Para ser mais preciso, seria necessário calcular se o projétil
    // atingiu alguma parte do tanque.
    // Por simplicidade, considerou-se que o tanque possui formato
    // esférico, com raio = 3/4 de seu comprimento. Esse é o chamado
    // "hitbox" do tanque.
    else
        return ((pos[0] - X[0])*(pos[0] - X[0]) +
               (pos[1] - X[1])*(pos[1] - X[1]) +
               (pos[2] - X[2])*(pos[2] - X[2]))
               < (HITBOX_TANQUE*HITBOX_TANQUE);
}

/**
 * Exibe os frames de morte do tanque.
 */
void Jogador::morte_proximo_frame()
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
void Jogador::meltdown()
{
    assert(anim_finalizada == false);

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
            this->anim_finalizada = true;
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
            mundo.cenario->criar_explosao(this->pos, RAIO_INCINERADOR * pow(2, variacao_morte - 1));
            this->anim_finalizada = true;
        }
    }

    // incrementa frame
    frame++;
}

/* -------------------------------------------------------------------------- */
/**
 * Função auxiliar que define a cor do tanque de acordo com o número do jogador.
 * A definição da cor segue a mesma sequência que no Tank Wars original.
 * A alteração da cor é realizada por referência.
 */
void definir_cor(float *cor, const int i)
{
    switch (i)
    {
        case 1:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.;
        break;

        case 2:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 3:
        cor[0] = 0.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 4:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 5:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 6:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 7:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 8:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.;
        break;

        case 9:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.5;
        break;

        case 10:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.5;
        break;
    }
}
