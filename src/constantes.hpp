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
 * Concentra as constantes utilizadas no jogo.
 */

/* Constantes gerais */
#define PI 3.14159265358979

/* Constantes utilizadas por municao.cpp e armas.cpp */
#define MASSA_MUNICAO       100.0
#define RAIO_INCINERADOR    100     // Raio do incinerador; os outros são baseados nesta.
#define QTD_INCINERADOR     100     // Qtd inicial de incineradores por jogador

#define FRACAO_RAIO_DANO    1.25    // Raio de dano / Raio de Explosao
#define GRAVIDADE           200.0
#define DT                  0.05    // Passo de integração.

/* Constantes utilizadas por mundo.hpp e mundo.c */
#define MAX_JOGADORES 10
