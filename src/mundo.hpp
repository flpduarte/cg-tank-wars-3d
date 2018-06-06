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
#ifndef MUNDO_HPP
#define MUNDO_HPP

#include "constantes.hpp"
#include "jogador.hpp"

/**
 * Mundo: Contém as variáveis de estado do mundo tais como tela atual, no. de
 * jogadores, etc.
 */
struct Mundo
{
    // Lista de jogadores. Só estarão ativos os jogadores de 0 a n_jogadores - 1
    Jogador *jogadores[MAX_JOGADORES];

    // configurações do jogo
    unsigned int n_jogadores;    // 2, ..., MAX_JOGADORES <= 10
    unsigned int n_rodadas;      // > 0

    // estado atual do mundo
    Tela tela_atual;
    unsigned int rodada_atual;   // 1, 2, ..., n_rodadas

    Mundo();
    ~Mundo();

};

#endif
