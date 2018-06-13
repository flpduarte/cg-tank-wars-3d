/**
 * mundo.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções definidas em mundo.hpp
 *
 */
#include <GL/glut.h>
#include <cstdlib>
#include "mundo.hpp"
#include "jogador.hpp"
#include "constantes.hpp"
#include "globals.hpp"
#include "configmenu.hpp"

/* Funções auxiliares */
/**
 * Deixa a tela preta e ajusta janela de recorte de forma que as Coordenadas do
 * Mundo coincidam com as Coordenadas da Tela.
 */
void preparar_tela_para_menu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glDisable(GL_LIGHTING);     // desativa efeitos de iluminação
    glDisable(GL_DEPTH_TEST);

    // Configura janela de recorte 2D para fazer coordenadas do mundo coincidir
    // com as coordenadas da tela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, JANELA_LARGURA, 0, JANELA_ALTURA);

    // inicia matriz model-view para exibir menu
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Cria o mundo ao iniciar o jogo.
 */
Mundo::Mundo()
{
    // Inicia os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogadores[i] = new Jogador(i + 1);
    }

    // Configurações padrão
    this->tela_atual  = TELA_INICIAL;
    this->n_jogadores = PADRAO_N_JOGADORES;
    this->n_rodadas   = PADRAO_N_RODADAS;
}

/**
 * Destroi o mundo ao final do jogo
 */
Mundo::~Mundo()
{

    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        delete this->jogadores[i];
    }
}

/**
 * Exibe a tela inicial do jogo.
 */
void Mundo::tela_inicial()
{
    // Configura a tela para ser a tela inicial e muda
    // o fundo da janela para preto
    this->tela_atual = TELA_INICIAL;
    preparar_tela_para_menu();

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_principal();
    this->menu_ativo->exibir();
}


/**
 * Exibe a tela de renomear jogadores
 */
void Mundo::renomear_jogadores()
{
    // Configura a tela para ser a tela inicial e muda
    // o fundo da janela para preto
    this->tela_atual = TELA_RENOMEAR_JOGADORES;
    preparar_tela_para_menu();

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_renomear_jogadores();
    this->menu_ativo->exibir();
}

/**
 * Exibe a tela de resultados parciais.
 * O incremento do número de vitórias deve ter sido feito ao finalizar a rodada,
 * imediatamente antes de chamar esta função.
 */
void Mundo::resultado_parcial()
{
    // Configura a tela para ser a tela inicial e muda o fundo da janela para preto
    this->tela_atual = TELA_RESULTADO_PARCIAL;
    preparar_tela_para_menu();

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_resultado_parcial();
    this->menu_ativo->exibir();
}


/**
 * Exibe o menu de compras para cada jogador.
 * Entrada: número do jogador: 1, 2, ..., n_jogadores
 */
void Mundo::tela_compras(unsigned int njogador)
{
    // Configura a tela para ser a tela inicial e muda o fundo da janela para preto
    this->tela_atual = TELA_COMPRAS;
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }

    // Enquanto njogador for um jogador válido, exibe menu de compras
    if (njogador <= this->n_jogadores)
    {
        preparar_tela_para_menu();
        this->menu_ativo = criar_menu_compras(jogadores[njogador - 1]);
        this->menu_ativo->exibir();
    }

    // Senão, inicia a próxima rodada
    else
    {
        this->inicia_rodada();
    }
}

/* --- Funções de interação com o usuário --- */

/**
 * Função responsável pela exibição dos itens na tela. É provavelmente a principal
 * função do jogo.
 *
 * Exibe os elementos na tela de acordo com cada estado do jogo.
 */
void Mundo::funcao_exibicao()
{
    switch (this->tela_atual)
    {
        // Exibe menu principal na tela inicial
        case TELA_INICIAL:
        case TELA_RODADA:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_COMPRAS:
        this->menu_ativo->exibir();
        break;

        case TELA_RESULTADO_PARCIAL:
        // TODO
        break;
    }
    glutPostRedisplay();
}


/**
 * Descreve a interação do usuário com o teclado, conforme cada estado do jogo.
 */
void Mundo::interacao_teclado(unsigned char tecla, int x, int y)
{
    switch (this->tela_atual)
    {
        case TELA_INICIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_RESULTADO_PARCIAL:
        case TELA_COMPRAS:
        this->menu_ativo->gerenciar_teclado(tecla);
        break;

        case TELA_RODADA:
        // TODO
        break;

    }
}


/**
 * Descreve a interação com as teclas especiais em cada parte do jogo, se houver.
 */
void Mundo::interacao_teclas_especiais(int tecla, int x, int y)
{
    switch (this->tela_atual)
    {
        case TELA_INICIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_RESULTADO_PARCIAL:
        case TELA_COMPRAS:
        this->menu_ativo->gerenciar_teclas_especiais(tecla);
        break;

        case TELA_RODADA:
        // TODO
        break;

    }
}


/**
 * Descreve a interação com o mouse conforme cada parte do jogo.
 * (deixei aqui para lembrar, mas talvez nem seja necessária)
 */
void Mundo::interacao_mouse(int botao, int estado, int x, int y)
{
    switch (mundo.tela_atual)
    {
        case TELA_INICIAL:
        // TODO
        break;

        case TELA_RENOMEAR_JOGADORES:
        // TODO
        break;

        case TELA_RODADA:
        // TODO
        break;

        case TELA_RESULTADO_PARCIAL:
        // TODO
        break;

        case TELA_COMPRAS:
        // TODO
        break;
    }
}
