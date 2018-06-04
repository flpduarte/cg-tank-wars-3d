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
    Tela tela_atual;
    int n_jogadores;
    Jogador *jogadores[MAX_JOGADORES];

    Mundo();
    ~Mundo();

};

#endif
