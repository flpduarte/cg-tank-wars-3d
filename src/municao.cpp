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
#include <cmath>
#include "constantes.hpp"
#include "municao.hpp"
#include "explosoes.hpp"

/* Implementação das funções da classe Municao */

/**
 * Valor da derivada do i-ésima variável de estado,
 * no instante atual. O tempo foi desprezado porque
 * não há nenhuma grandeza que dependa do tempo.
 */
double Municao::derivada(int i)
{
    // Derivada da posição = velocidade
    if (i < 3)
    {
        return X[i + 3];
    }

    // Derivada da velocidade = aceleração.
    // Aceleração = Força / Massa.
    // Esta função calcula a aceleração componente por componente.
    else
    {
        return F[i - 3]/massa;
    }
}

/**
 * atualizar_posicao()
 * Usa o método de integração de Euler para atualizar as variáveis de estado
 */
void Municao::atualizar_posicao()
{
    for (int i = 0; i < 6; i++)
    {
        X[i] += derivada(i) * DT;
    }
}


/**
 * lancar(X0, V0, angulo, vento)
 * Define as coordenadas iniciais do projétil na tela ao ser lançado.
 */
void Municao::lancar(int X0[3], int V0, int ang, int vento)
{
    // Posição
    X[0] = X0[0];
    X[1] = X0[1];
    X[2] = X0[2];

    // Velocidade
    X[3] = V0*cos(ang);     // Vx
    X[4] = 0;               // Vy
    X[5] = V0*sin(ang);     // Vz

    // Forças
    F[0] =  massa*vento;        // Efeito do vento
    F[1] =  0.;
    F[2] = -massa*GRAVIDADE;    // Efeito da gravidade
}


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
