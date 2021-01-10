/**
 * interacoes.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções necessárias pelo OpenGL para realizar:
 * - Interações com Teclado - teclas normais e especiais
 * - Interação com o Mouse (se houver)
 * - Função principal de exibição
 * - Função de animação, se necessária.
 *
 * Obs: As implementações foram passadas para a classe Mundo.
 * Como o OpenGL exige que as funções a serem passadas para glutKeyboardFunc(),
 * glutMouseFunc(), etc. sejam *estáticas* ou "standalone", então as implemen-
 * tações aqui apenas chamarão suas funções correspondentes no objeto global
 * mundo. Ou seja, aqui elas são apenas um "Wrap".
 *
 * Isso permitirá acessar todas as propriedades do mundo.
 * https://stackoverflow.com/questions/23774223/cannot-convert-classnameglutkeyboard-from-type-void-classnameunsigned
 */
#include "../include/interacoes.hpp"
#include "../include/globals.hpp"
#include <iostream>

/**
 * Função responsável pela exibição dos itens na tela. É provavelmente a principal
 * função do jogo.
 *
 * Exibe os elementos na tela de acordo com cada estado do jogo.
 */
void funcao_exibicao()
{
    mundo.funcao_exibicao();
}


/**
 * Descreve a interação do usuário com o teclado, conforme cada estado do jogo.
 */
void interacao_teclado(unsigned char tecla, int x, int y)
{
    mundo.interacao_teclado(tecla, x, y);
}


/**
 * Descreve a interação com as teclas especiais em cada parte do jogo, se houver.
 */
void interacao_teclas_especiais(int tecla, int x, int y)
{
    mundo.interacao_teclas_especiais(tecla, x, y);
}


/**
 * Descreve a interação com o mouse conforme cada parte do jogo.
 */
void interacao_mouse(int botao, int estado, int x, int y)
{
    mundo.interacao_mouse(botao, estado, x, y);
}