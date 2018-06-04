/**
 * interacoes.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções necessárias pelo OpenGL para realizar:
 * - Interações com Teclado - teclas normais e especiais
 * - Interação com o Mouse (se houver)
 * - Função principal de exibição
 * - Função de animação, se necessária.
 */
#include "constantes.hpp"
#include "globals.hpp"
#include "interacoes.hpp"

/**
 * Função responsável pela exibição dos itens na tela. É provavelmente a principal
 * função do jogo.
 *
 * Exibe os elementos na tela de acordo com cada estado do jogo.
 */
void funcao_exibicao()
{
    switch (estado_do_mundo.tela_atual)
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


/**
 * Descreve a interação do usuário com o teclado, conforme cada estado do jogo.
 */
void interacao_teclado(unsigned char tecla, int x, int y)
{
    switch (estado_do_mundo.tela_atual)
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


/**
 * Descreve a interação com as teclas especiais em cada parte do jogo, se houver.
 */
void interacao_teclas_especiais(int key, int x, int y)
{
    switch (estado_do_mundo.tela_atual)
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


/**
 * Descreve a interação com o mouse conforme cada parte do jogo.
 */
void interacao_mouse(int botao, int estado, int x, int y)
{
    switch (estado_do_mundo.tela_atual)
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
