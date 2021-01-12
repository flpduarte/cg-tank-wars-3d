/**
 * cenario.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Declara a classe Cenario: armazena as informações sobre o cenário
 * da rodada atual:
 * - Ordem em que os jogadores aparecem da esquerda para a direita;
 * - Posição da câmera
 * - Terreno atual
 * - etc.
 */

// desativar asserts qdo programa estiver funcionando
//#define NDEBUG
#include <GL/glut.h>
#include <cenario/Cenario.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <iostream>
#include <random>
#include <objetos2D.hpp>
#include <constantes.hpp>
#include <graphics/cor.h>
#include <objetos/armas/armas.hpp>
#include <objetos/jogador.hpp>
#include <cenario/Terreno.h>

#include <objetos/explosoes/Explosao.h>
#include <cenario/Projetil.h>

/* --- Implementação da classe Cenario --- */

// OBSERVAÇÕES SOBRE AS CONSTANTES ESTÁTICAS DA CLASSE:
//
// "Note that the constant initializer is not a definition. You still need to define the static member in an
// enclosing namespace."
// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr038.htm
//
// Resumindo, as expressões em cenario.hpp declaram, mas NÃO INICIAM, as constantes. Para de fato INICIAR
// as constantes (criá-las - para posteriormente receberem o valor definido em cenario.hpp), é preciso
// escrever as linhas abaixo fora da definição da classe:
constexpr GLfloat Cenario::SOMBRA[];
constexpr GLfloat Cenario::POSICAO_SOL[];
constexpr GLfloat Cenario::COR_SOL[];
// Isso porque as demais constantes só serão criadas APÓS A EXECUÇÃO DO CONSTRUTOR (lazy initialization).
// Logo, as linhas acima são obrigatórias para cada constante estática que precise ser iniciada
// antes da execução do construtor.

// Iniciação do engine para geração de números aleatórios
std::default_random_engine Cenario::gerador = std::default_random_engine();

/**
 * Cria um novo cenário: Terreno, câmera e ordem de aparecimento dos jogadores.
 */
Cenario::Cenario(const std::vector<Jogador *> &listaJogadores)
{
    // Cria câmera e terreno
    srand(time(NULL));
    terreno   = new Terreno;

    // Configura cenário
    criarListaDeTanquesEmOrdemAleatoria(listaJogadores);
    posicionarTanques();

    n_jogadores_vivos   = tanques.size();
    projetil            = nullptr;
    explosao            = nullptr;
    tanqueMorrendo      = nullptr;
    vento               = definir_vento();
    tanqueNaVez         = selecionarElementoAleatorio(tanques.begin(), tanques.end());
    tanqueEmFoco        = &(*tanqueNaVez);

    // Configura iluminação do Sol.
    // Obs: Posso futuramente fazer essas configurações mudarem aleatoriamente,
    // para criar cenários noturnos, por exemplo. Mas isto está fora do escopo
    // do trabalho atual.
    glLightfv(GL_LIGHT0, GL_AMBIENT, SOMBRA);           //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL);          //contribuição difusa
    glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Prepara para iniciar vez do jogador atual
    tanqueNaVez->preparar_para_jogar();
    controle_jogador    = true;                    // Jogador já começa ativo
}

int Cenario::getVento() const {
    return vento;
}

int Cenario::getGravidade() const {
    return GRAVIDADE;
}

void Cenario::criarListaDeTanquesEmOrdemAleatoria(std::vector<Jogador *> const &listaJogadores) {

    // Cria uma lista de inteiros de 0 a nJogadores
    std::vector<int> numeroJogadores;
    for (int i = 0; i < listaJogadores.size(); i++) {
        numeroJogadores.emplace_back(i);
    }

    // Mistura os inteiros
    std::shuffle(numeroJogadores.begin(), numeroJogadores.end(), gerador);
    // std::shuffle(tanques.begin(), tanques.end(), std::mt19937(std::random_device()()));

    // Cria os tanques a partir da lista misturada de inteiros
    for (int i : numeroJogadores) {
        tanques.emplace_back(Tanque(*listaJogadores[i]));
    }
}


/**
 * Após definir a ordem em que os jogadores aparecem, distribuí-los sobre o
 * terreno.
 *
 * Posicionamento:
 * - primeiro jogador:x = 10; (pode variar entre 8 e 12)
 * - último jogador:  x = 90;
 *
 * Restante dos jogadores é posicionado uniformemente num intervalo de 80.
 *
 * J1 ----- J2 ----- J3 ------ J4 ------ J5
 *
 * Passo = (n_jogadores - 1) / 80
 */
void Cenario::posicionarTanques()
{
    double passo = 80. / (double)(tanques.size() - 1);
    double x0    = (double) 8 + rand() % 4;
    int n_jogadores = tanques.size();

    for (int i = 0; i < n_jogadores; i++)
    {
        double x = x0 + i*passo;
        double pos[3] = {x, 0, terreno->z(x, 0)};
        tanques[i].posicionar(pos);
        tanques[i].definir_normal(terreno->normal(x, 0));
    }

    // ajusta ângulo inicial dos canhoes dos tanques nas extremidades
    tanques[0].setAnguloPara75Direita();
    tanques[n_jogadores - 1].setAnguloPara75Esquerda();
}

/**
 * Escolhe um tanque aleatoriamente do vetor de tanques.
 * @return o iterador para o tanque escolhido.
 */
template<typename iteratorType>
iteratorType Cenario::selecionarElementoAleatorio(iteratorType first, iteratorType last) {
    // Seja "distancia" uma variável aleatória com distribuição uniforme, no intervalo [0, n - 1].
    // Cada chamada de distancia(gerador) gera um novo número nesse intervalo.
    std::uniform_int_distribution<> distancia(0, std::distance(first, last));
    auto primeiroElemento = first;
    std::advance(primeiroElemento, distancia(gerador));
    return primeiroElemento;
}

/**
 * Destroi cenário após o fim da rodada.
 */
Cenario::~Cenario()
{
    // Desativa efeito de iluminação
    glDisable(GL_LIGHT0);

    // Remove vetores criados
    delete terreno;
    delete projetil;
    delete explosao;
}

/* --- Funções privadas --- */
/**
 * Define um vento aleatório, na faixa de intensidades definida pela configuração
 * do jogo.
 *
 * TODO: implementar esta função posteriormente.
 */
int Cenario::definir_vento()
{
    return 0;
}

/**
 * Exibe o cenario na tela:
 * Cria viewport para exibir o cenario 3D
 * Sobre o cenario, cria um viewport 2D para exibir informações do jogador atual
 * No cenario 3D, mostrar:
 * - Terreno
 * - Tanques
 * - Tiro e Explosões, se for o caso.
 *
 * Note que aqui precisarei lidar com 2 viewports diferentes.
 *
 * Posso usar glScissor(left, bottom, width, height) para definir uma região em
 * Coordenadas da TelaAtual que receberá desenhos. Isso permitirá limpar somente par-
 * te da tela, por exemplo. Usarei glScissor para limpar cada viewport com uma
 * corBase diferente.
 *
 * Ideia:
 * 1. Desenhar as informações em 2D na tela, antes de exibir cenário 3D.
 *    Deve-se garantir que não haverá conflitos entre os dados 2D e o cenário 3D.
 * 2. Definir o viewport 3D e desenhar o cenário.
 */
void Cenario::exibir()
{
    desenhar_na_viewport2D();
    desenhar_na_viewport3D();
}


/**
 * Desenha as informações sobre a imagem 3D:
 * - Vento, anguloCanhao, potencia, arma atual, etc.
 *
 * As informações são exibidas antes de exibir o cenário em 3D. Em outras pala-
 * vras, o cenário 3D é desenhado sobre as informações 2D. Considerei o viewport
 * 2D como sendo a tela inteira; tomar cuidado para não exibir nenhuma informação
 * onde depois será posicionado a viewport 3D.
 */
void Cenario::desenhar_na_viewport2D()
{
    // Limpa a tela para cinza escuro. Assume que Scissor está desligado.
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // define janela de recorte de forma a coincidir
    // coordendas do mundo com coordenadas da janela
    // Nota: Redefinir viewport para ser janela inteira.
    // glLoadIdentity() tem efeito sobre a matriz ativa, mas não faz nada com a viewport!
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, JANELA_LARGURA, 0, JANELA_ALTURA);
    glViewport(0, 0, JANELA_LARGURA, JANELA_ALTURA);   // redefine viewport para ser a janela inteira.

    // Imprime nome do jogador *ativo* no centro da primeira linha
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(JANELA_LARGURA/2, POS_PRIMEIRA_LINHA, 0);
    desenharTextoCentralizado(tanqueEmFoco->getNome(), TAM_TEXTO, FONTE, tanqueEmFoco->getCor());
    glPopMatrix();

    // 2a linha: anguloCanhao à esquerda, Arma à direita
    // Informações são referentes ao jogador da vez atual (nao necessariamente
    // o jogador ativo)
    glPushMatrix();
    glTranslatef(ESPACAMENTO, POS_SEGUNDA_LINHA, 0);
    float larg = desenhar_string("Angulo: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPushMatrix();
    glTranslatef(larg, 0, 0);
    desenhar_string(tanqueNaVez->getAnguloEmString(), TAM_TEXTO, FONTE, cor::AMARELO);
    glPopMatrix();

    glTranslatef(JANELA_LARGURA - 2*ESPACAMENTO, 0, 0);
    larg = texto_alinhado_direita(tanqueNaVez->getNomeDaArmaAtual(), TAM_TEXTO, FONTE, cor::AMARELO);
    glTranslatef(-larg, 0, 0);
    texto_alinhado_direita("Arma: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPopMatrix();

    // 3a Linha: Potencia e Homens
    glPushMatrix();
    glTranslatef(ESPACAMENTO, POS_TERCEIRA_LINHA, 0);
    larg = desenhar_string("Potencia: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPushMatrix();
    glTranslatef(larg, 0, 0);
    desenhar_string(std::to_string(tanqueNaVez->getPotencia()), TAM_TEXTO, FONTE, cor::AMARELO);
    glPopMatrix();

    glTranslatef(JANELA_LARGURA - 2*ESPACAMENTO, 0, 0);
    larg = texto_alinhado_direita(std::to_string(tanqueNaVez->getNumeroDeHomens()), TAM_TEXTO, FONTE, cor::AMARELO);
    glTranslatef(-larg, 0, 0);
    texto_alinhado_direita("Homens: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPopMatrix();
}


/**
 * Configura a viewport 3D principal e desenha o cenário na viewport.
 */
void Cenario::desenhar_na_viewport3D()
{
    // Configura GL_SCISSOR para coincidir com viewport para limpar a tela com
    // corBase azul celeste
    glScissor(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(cor::AZUL_CELESTE[0], cor::AZUL_CELESTE[1], cor::AZUL_CELESTE[2], cor::AZUL_CELESTE[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Ativa iluminação e teste de profundidade
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    // Configura Viewport e Projeção Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, ASPECT_RATIO, DNEAR, DFAR);
    glViewport(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);

    // Muda para matriz ModelView, posiciona a câmera e desenha o cenário
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    posicionar_camera();
    this->desenhar();
}

/**
 * desenhar()
 * Função responsável por desenhar todos os objetos 3D que compõem o cenário.
 */
void Cenario::desenhar()
{
    // Desenha o terreno
    terreno->desenhar();

    // Desenha os jogadores
    for (auto tanque : tanques) {
        if (tanque.visivel) {
            tanque.desenhar();
        }
    }

    // Desenha o projétil, se houver
    if (projetil != nullptr)
    {
        projetil->desenhar();
    }

    // Desenha a explosão, se houver
    if (explosao != nullptr)
    {
        explosao->desenhar();
    }
}

/**
 * Funções que respondem ao teclado: teclas comuns e teclas especiais.
 * Nota: durante os eventos de voo do projétil ou outras animações, o
 * estado controle_jogador é falso e o jogo não responderá aos coman-
 * dos do teclado.
 */
void Cenario::gerenciar_teclado(unsigned char tecla)
{
    // Não faz nada se o jogador nao estiver no controle.
    if (!controle_jogador)
        return;

    // Por enquanto a unica tecla a que o jogo responde é o espaço.
    // O restante é via teclas especiais.
    // Implementar outras teclas à medida que o jogo evoluir.
    // Ex: 1, 2, ..., 9, 0: exibe uma janela com informações do
    // jogador selecionado.
    switch (tecla)
    {
        // Espaço: atirar!
        // Cria um projétil no cenário; desativa controle do jogador.
        // Muda estado do cenário para ativar a animação do projétil
        case ' ':
            controle_jogador = false;
            projetil = tanqueNaVez->atirar(this);
            glutTimerFunc(DT_ANIMACAO, Cenario::animacao_projetil, 1);    // ativa animacao
            break;

            // Tab: muda o armamento
        case '\t':
            tanqueNaVez->selecionarProximaArma();
            break;

        default:
            std::cout << "Tecla pressionada: <" << tecla << '>' << '\n';
    }
    glutPostRedisplay();
}


/**
 * Teclas especiais usadas:
 * Setas esquerda e direita: ajustam ângulo
 * Setas para cima e para baixo: ajustam potência
 * Page up/Page down: Aumentam/diminuem a potência de 100 em 100
 */
void Cenario::gerenciar_teclas_especiais(int tecla)
{
    if (!controle_jogador)
        return;

    switch (tecla)
    {
        case GLUT_KEY_LEFT:
            tanqueNaVez->incrementarAnguloSentidoHorario();
            break;

        case GLUT_KEY_RIGHT:
            tanqueNaVez->incrementarAnguloSentidoAntiHorario();
            break;

        case GLUT_KEY_UP:
            tanqueNaVez->aumentarPotenciaLento();
            break;

        case GLUT_KEY_PAGE_UP:
            tanqueNaVez->aumentarPotenciaRapido();
            break;

        case GLUT_KEY_DOWN:
            tanqueNaVez->diminuirPotenciaLento();
            break;

        case GLUT_KEY_PAGE_DOWN:
            tanqueNaVez->diminuirPotenciaRapido();
            break;
    }
}

/**
 * Funções responsáveis pela animação do projétil.
 * Para ser chamada, assume que this->projetil != NULL.
 */
void Cenario::animacao_projetil(int valor)
{
    mundo.cenario->animar_projetil();
    glutPostRedisplay();
}

void Cenario::animar_projetil()
{
    // atualiza a posição do projétil
    assert(this->projetil != nullptr);
    projetil->atualizar_posicao();

    // Se projétil atingiu um obstáculo, cria uma explosão no local atual
    if (ocorreuColisaoEntreProjetilEObstaculo())
    {
        explosao = projetil->detonar();
        delete projetil;
        projetil = nullptr;
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_explosao, 0);   // 0 = explosao projetil
    }

    // Caso contrário, continua a animação do projétil
    else
    {
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_projetil, 1);
    }
}

/**
 * Verifica se a posição dada localiza-se dentro de algum obstáculo: tanque ou terreno.
 * Por simplicidade, será considerado que o projétil é uma esfera, para fins de detecção de colisão.
 *
 * @return true, se o projétil atingiu o terreno ou um tanque; false caso contrário.
 */
bool Cenario::ocorreuColisaoEntreProjetilEObstaculo()
{
    return atingiuTerreno() || atingiuUmTanque();
}

bool Cenario::atingiuTerreno() {
    double x = projetil->getPosicao()[0];
    double y = projetil->getPosicao()[1];
    double z = projetil->getPosicao()[2];
    return (z - getCoordenadaZ(x, y) <= projetil->getRaio());
}

bool Cenario::atingiuUmTanque() {
    bool atingiu = false;
    for (auto tanque = tanques.cbegin(); !atingiu && tanque != tanques.end(); ++tanque)
    {
        // todo: revisar este método de detecção de colisão
        atingiu = tanque->atingiu(projetil->getPosicao());
    }
    return atingiu;
}

/**
 * Funções responsáveis pela animação da explosão.
 * Assume que existe explosão ocorrendo no cenário.
 */
void Cenario::animacao_explosao(int value)  // static
{
    mundo.cenario->animar_explosao();
    glutPostRedisplay();
}

void Cenario::animar_explosao()
{
    // Confirma que existe explosão no cenário
    assert(explosao != nullptr);

    // Chamar esta função continuamente enquanto a animação não tiver terminado.
    if (explosao->proximo_frame()) // true enquanto animação não terminar
    {
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_explosao, 0);
    }

        // Caso contrário, analisa os danos causado pela explosão.
    else
    {
        this->analisar_danos();
    }
}


/**
 * analisar_danos()
 * Atualiza o número de homens dos jogadores após a explosão.
 * Apaga o objeto explosao ao final da tarefa.
 *
 * Caso um jogador tenha morrido com a explosão, insere-o em uma
 * fila para executar as animações de morte daquele jogador.
 */
void Cenario::analisar_danos()
{
    // Confirma que existe explosão. Esta função é chamada por animar_explosao().
    assert(this->explosao != nullptr);

    registrarDanoAosTanquesAfetados();

    // Apaga o objeto explosão
    delete explosao;
    explosao = nullptr;

    // Voltar para o loop de executar a animação de saída dos jogadores
    retirar_jogadores_mortos();
}

void Cenario::registrarDanoAosTanquesAfetados() {
    // Itera pelos jogadores vivos no cenário e atualiza seus respectivos números
    // de homens.
    for (auto &tanque : tanques)
    {
        if (tanque.isVivo())
        {
            tanque.removerHomens(explosao->dano(tanque.getPosicao()));
            tanque.setCorBaseadoNoNumeroDeHomens();

            // Inclui jogador na fila para executar animação de morte se ele morreu.
            if (!tanque.isVivo())
            {
                filaTanquesMortos.push(&tanque);
            }
        }
    }
}

/**
 * Loop que executa a animação de cada jogador que está na fila de
 * jogadores mortos.
 *
 * Após executar cada animação, muda a flag "vivo" para false do jogador,
 * a fim de que ele não seja mais exibido no cenário.
 *
 * Quando não houver mais jogadores com homens = 0 para executar animação,
 * a função verifica se há mais de 1 jogador no cenário.
 *
 * Se houver, devolve o controle para o próximo jogador da vez.
 * Caso contrário, dá a vitória ao jogador vivo e encerra o cenário.
 */
void Cenario::retirar_jogadores_mortos()
{
    // Executa animações de morte.
    if (!filaTanquesMortos.empty())
    {
        // retira índice do jogador da fila e o salva na variável tanqueMorrendo
        tanqueMorrendo = filaTanquesMortos.front();
        tanqueEmFoco = tanqueMorrendo;
        n_jogadores_vivos--;                                // menos 1 jogador vivo

        filaTanquesMortos.pop();
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_morte_jogador, 1);
    }

        // Se não houver mais jogadores na fila, verificar se encerra o jogo ou se
        // muda a vez para o próximo jogador.
    else
    {
        tanqueMorrendo = nullptr;
        if (this->rodada_encerrou())
        {
            // dá um pequeno intervalo entre a ultima animação e ir para o
            // resultado parcial.
            glutTimerFunc(500, resultado_parcial, 0);           // TODO: modificar esta operação para ser executada pelo objeto Mundo.
        }

            // Iniciar a vez do próximo jogador
        else
        {
            iniciar_vez_do_proximo_jogador();
        }
    }
}


/**
 * rodada_encerrou()
 * Verifica número de jogadores vivos.
 * - 2 ou mais jogadores vivos: retorna false.
 * - 1 jogador vivo: incrementa o número de vitórias desse jogador.
 *   Retorna true.
 * - 0 jogadores vivos: retorna true.
 */
bool Cenario::rodada_encerrou()
{
    // 0 ou 1 jogador - rodada encerrou.
    bool encerrou = (n_jogadores_vivos < 2);

    // incrementar número de vitórias ao jogador que sobrou
    if (n_jogadores_vivos == 1)
    {
        registrarVitoriaAosTanquesSobreviventes();
    }

    return encerrou;
}

void Cenario::registrarVitoriaAosTanquesSobreviventes() const {
    for (auto tanque : tanques) {
        if (tanque.isVivo()) {
            tanque.registrarVitoria();
        }
    }
}

/**
 * Inicia a vez do próximo jogador.
 * Assume que há pelo menos 2 jogadores vivos!
 */
void Cenario::iniciar_vez_do_proximo_jogador()
{
    assert (n_jogadores_vivos > 1);
    do
    {
        ++tanqueNaVez;
        if (tanqueNaVez == tanques.end())
            tanqueNaVez = tanques.begin();
    }
    while (!tanqueNaVez->isVivo());

    // Faz jogador da vez tmb ser o jogador ativo e segue o jogo!
    tanqueEmFoco = &*tanqueNaVez;
    tanqueNaVez->preparar_para_jogar();
    controle_jogador = true;
}

/**
 * Funções responsáveis pela animação da morte de um jogador.
 * Manipula a variável tanqueMorrendo.
 */
void Cenario::animacao_morte_jogador(int value)
{
    mundo.cenario->animar_morte_jogador();
    glutPostRedisplay();
}

void Cenario::animar_morte_jogador()
{
    tanqueMorrendo->morte_proximo_frame();
    if (tanqueMorrendo->isAnimacaoFinalizada())
    {
        explosao = tanqueMorrendo->gerarExplosaoAdicional();
        tanqueMorrendo->visivel = false;
        tanqueMorrendo = nullptr;

        // Anima uma eventual explosao que a animação possa ter criada.
        if (explosao != nullptr)
        {
            glutTimerFunc(DT_ANIMACAO, animacao_explosao, 0);
        }

        // Senão, volta para retirar_jogadores_mortos()
        else
        {
            retirar_jogadores_mortos();
        }
    }
    else
    {
        glutTimerFunc(DT_ANIMACAO, animacao_morte_jogador, 1);
    }
}

/**
 * getCoordenadaZ(): Retorna a posição z do solo na posição (x, y) dada.
 */
double Cenario::getCoordenadaZ(double const x, double const y)
{
    return this->terreno->z(x, y);
}

void Cenario::posicionar_camera()
{
    gluLookAt(CAMERA_POS[0], CAMERA_POS[1], CAMERA_POS[2],
              CAMERA_LOOKAT[0], CAMERA_LOOKAT[1], CAMERA_LOOKAT[2],
              CAMERA_VIEWUP[0], CAMERA_VIEWUP[1], CAMERA_VIEWUP[2]);
}
