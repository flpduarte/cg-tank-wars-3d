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
#define PADRAO_N_JOGADORES 2


/* Dimensões e posição da janela */
#define JANELA_LARGURA     800
#define JANELA_ALTURA      600
#define JANELA_POSICAO_X   50
#define JANELA_POSICAO_Y   100
#define JANELA_TITULO      "Tank Wars 3D"

/* Constantes utilizadas por municao.cpp e armas.cpp */
#define MASSA_MUNICAO       100.0
#define RAIO_INCINERADOR    100     // Raio do incinerador; os outros são baseados nesta.
#define QTD_INCINERADOR     100     // Qtd inicial de incineradores por jogador

#define FRACAO_RAIO_DANO    1.25    // Raio de dano / Raio de Explosao
#define GRAVIDADE           200.0
#define DT                  0.05    // Passo de integração.

/* Constantes utilizadas por mundo.hpp e mundo.c */
#define MAX_JOGADORES 10

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
