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

#include "mundo.hpp"
#include "jogador.hpp"
#include "constantes.hpp"

/**
 * Cria o mundo ao iniciar o jogo.
 */
Mundo::Mundo()
{
    this->tela_atual = TELA_INICIAL;
    this->n_jogadores = PADRAO_N_JOGADORES;

    // Inicia os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogadores[i] = new Jogador(i + 1);
    }
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
