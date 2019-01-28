/**
 * mundo.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções definidas em mundo.hpp
 *
 */

// para desativar asserts, ativar este comando antes de #define <cassert>
//#define NDEBUG
#include <GL/glut.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "../include/armas.hpp"
#include "../include/cenario.hpp"
#include "../include/mundo.hpp"
#include "../include/jogador.hpp"
#include "../include/constantes.hpp"
#include "../include/globals.hpp"
#include "../include/configmenu.hpp"



/* Funções auxiliares */

/**
 * Deixa a tela preta e ajusta janela de recorte de forma que as Coordenadas do
 * Mundo coincidam com as Coordenadas da Tela.
 */
void preparar_tela_para_menu()
{
    // Limpa a tela
    glClear(GL_COLOR_BUFFER_BIT);

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
    // Cria lista global de armamentos
    criar_lista_global_armamentos();

    // Inicia os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogadores[i] = new Jogador(i + 1);
    }

    // Configurações padrão
    this->tela_atual  = TELA_INICIAL;
    this->n_jogadores = PADRAO_N_JOGADORES;
    this->n_rodadas   = PADRAO_N_RODADAS;
    this->menu_ativo  = NULL;
    this->cenario     = NULL;
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
 * Transiciona para a tela inicial
 */
void Mundo::tela_inicial()
{
    // Muda a tela atual
    this->tela_atual = TELA_INICIAL;

    // Configura a tela do menu principal
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);         // funcionalidade q permite desenhar em apenas parte da tela
    glClearColor(0, 0, 0, 0);

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_principal();

    // Avisa que é preciso redesenhar a tela.
    // Isto provoca uma chamada ao glutDisplayFunc.
    glutPostRedisplay();
}


/**
 * Transiciona para a tela de renomear jogadores.
 * Não é preciso mudar configurações de exibição: isto já foi feito para o menu
 * principal.
 */
void Mundo::renomear_jogadores()
{
    // Muda a tela atual
    this->tela_atual = TELA_RENOMEAR_JOGADORES;

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_renomear_jogadores();
    glutPostRedisplay();
}

/**
 * Configura o mundo para iniciar o jogo
 */
void Mundo::iniciar_jogo()
{
    // Zera todas as variáveis do jogo
    rodada_atual = 0;
    for (int i = 0; i < n_jogadores; i++)
    {
        jogadores[i]->condicao_inicial();
    }

    // Inicia a primeira rodada
    this->iniciar_rodada();
}

/**
 * Inicia a rodada - configura o cenário
 */
void Mundo::iniciar_rodada()
{
    // Espera-se que o cenário deva estar desativado
    assert(cenario == NULL);

    // Muda a tela ativa
    this->tela_atual = TELA_RODADA;

    // Remove menus da memória
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
        this->menu_ativo = NULL;
    }

    // Prepara para início da rodada
    rodada_atual++;
    for (int i = 0; i < n_jogadores; i++)
    {
        jogadores[i]->reiniciar();
    }

    // Cria um novo cenário
    cenario = new Cenario;
    glutPostRedisplay();
}


/**
 * Exibe a tela de resultados parciais.
 * O incremento do número de vitórias deve ter sido feito ao finalizar a rodada,
 * imediatamente antes de chamar esta função.
 */
void Mundo::resultado_parcial()
{
    // Remove cenário
    if (this->cenario != NULL)
    {
        delete this->cenario;
        this->cenario = NULL;
    }

    // Transiciona para a tela de resultado parcial
    this->tela_atual = TELA_RESULTADO_PARCIAL;

    // Configura a tela de resultado parcial
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0, 0);

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_resultado_parcial();
    glutPostRedisplay();
}


/**
 * Exibe o menu de compras para cada jogador.
 * Entrada: número do jogador: 1, 2, ..., n_jogadores
 */
void Mundo::tela_compras(int njogador)
{
    // Transiciona para a tela de compras. Usa as mesmas Configurações
    // que a tela de resultado parcial.
    this->tela_atual = TELA_COMPRAS;
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }

    // Enquanto njogador for um jogador válido, exibe menu de compras
    if (njogador <= this->n_jogadores)
    {
        this->menu_ativo = criar_menu_compras(jogadores[njogador - 1]);
        glutPostRedisplay();
    }

    // Senão, inicia a próxima rodada
    else
    {
        this->iniciar_rodada();
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
        case TELA_RESULTADO_PARCIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_COMPRAS:
            preparar_tela_para_menu();
            this->menu_ativo->exibir();
            break;

        // Exibe o cenário
        case TELA_RODADA:
            this->cenario->exibir();
            break;
    }

    // redesenha a tela
    glFlush();
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
            this->cenario->gerenciar_teclado(tecla);
            break;
    }
    glutPostRedisplay();
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
            this->cenario->gerenciar_teclas_especiais(tecla);
            break;

    }
    glutPostRedisplay();
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
