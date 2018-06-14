/**
 * constantes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Concentra as constantes e tipos enumerados utilizadas no jogo.
 */
#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

/* Constantes gerais */
#define PI 3.14159265358979

/* Configuração padrão do jogo */
#define PADRAO_N_JOGADORES  2
#define PADRAO_N_RODADAS    10
#define MAX_CARACTERES_NOME 15

/* Dimensões e posição da janela */
#define JANELA_LARGURA     800
#define JANELA_ALTURA      600
#define JANELA_POSICAO_X   50
#define JANELA_POSICAO_Y   100
#define JANELA_TITULO      "Tank Wars 3D"

/* Dimensões padrão das opções de menu */
#define OPCAOMENU_LARGURA_PADRAO 200
#define OPCAOMENU_ALTURA_PADRAO  50         // inclui borda
#define OPCAOMENU_POSX_PADRAO    0
#define OPCAOMENU_POSY_PADRAO    JANELA_ALTURA - OPCAOMENU_ALTURA_PADRAO
#define OPCAOMENU_LARGURA_BORDA  5

/* Constantes utilizadas por municao.cpp e armas.cpp */
#define MASSA_MUNICAO       100.0
#define RAIO_INCINERADOR    100     // Raio do incinerador; os outros são baseados nesta.
#define QTD_INCINERADOR     100     // Qtd inicial de incineradores por jogador

#define FRACAO_RAIO_DANO    1.25    // Raio de dano / Raio de Explosao
#define GRAVIDADE           200.0
#define DT                  0.05    // Passo de integração.

/* Constantes utilizadas por mundo.hpp e mundo.c */
#define MAX_JOGADORES 10

/* Definição de algumas cores padrão */
namespace cor
{
    const float PRETO[]    = {0, 0, 0};
    const float VERMELHO[] = {1, 0, 0};
    const float VERDE[]    = {0, 1, 0};
    const float AZUL[]     = {0, 0, 1};
    const float AMARELO[]  = {1, 1, 0};
    const float CIANO[]    = {0, 1, 1};
    const float LILAS[]    = {1, 0, 1};
    const float BRANCO[]   = {1, 1, 1};
    const float CINZA_MEDIO[] = {0.5, 0.5, 0.5};
    const float CINZA_ESCURO[] = {0.2, 0.2, 0.2};

    // Função auxiliar que copia os valores de cor da variável origem à variável dest.
    void definir_cor(float *dest, const float *origem);
}


/* Tipos enumerados */
/**
 * Tela: tipo enumerado para definir qual é a tela atual ativa.
 */
enum Tela
{
    TELA_INICIAL,
    TELA_RENOMEAR_JOGADORES,
    TELA_RODADA,
    TELA_RESULTADO_PARCIAL,
    TELA_COMPRAS
};

#endif
