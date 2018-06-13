/**
 * jogador.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções não abstratas da classe Municao e da classe
 * MunicaoExplosiva.
 */

/* Bibliotecas */
#include "constantes.hpp"
#include "municao.hpp"
#include "explosoes.hpp"


/* Implementação das funções da classe MunicaoExplosiva */
/**
 * Construtor da MunicaoExplosiva define apenas a sua massa.
 * É igual para todas as munições.
 */
MunicaoExplosiva::MunicaoExplosiva()
{
    this->massa = MASSA_MUNICAO;
}

/**
 * detonar(): Executa a função que produz o efeito de explosão na posição
 * atual do armamento.
 */
void MunicaoExplosiva::detonar()
{
    int pos[3] = {(int) X[0], (int) X[1], (int) X[2]};
    efeito_explosao(pos, this->raio_explosao());
}
