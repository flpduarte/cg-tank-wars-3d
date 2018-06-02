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
 * Define a classe Mundo e outros dados associados.
 *
 */

#include "constantes.hpp"
#include "jogador.hpp"

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

/**
 * Mundo: Contém as variáveis de estado do mundo tais como tela atual, no. de
 * jogadores, etc.
 */
class Mundo
{
    Tela tela_atual;
    int n_jogadores;
    Jogador jogadores[MAX_JOGADORES];
};
