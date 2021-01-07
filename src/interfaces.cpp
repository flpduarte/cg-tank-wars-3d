/**
 * interfaces.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa os métodos não abstratos das interfaces.
 */
#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include "../include/armas.hpp"
#include "../include/cenario.hpp"
#include "../include/jogador.hpp"
#include "../include/interfaces.hpp"
#include "../include/constantes.hpp"
#include "../include/auxiliares.hpp"
#include "../include/globals.hpp"
#include "ui/Menu.hpp"


/* --- Implementação das funções da classe Menu --- */
/**
 * Inicia objeto Menu
 */


/* --- Implementação das funções da classe Municao --- */

double Municao::massa()
{
    return m;
}

/* --- Implementação das funções da classe Projetil --- */
/**
 * Cria um novo projétil com condições iniciais dadas.
 * A condição inicial - posição e vetor velocidade - é calculada pelo objeto
 * Jogador que lança o projétil.
 */
Projetil::Projetil(Municao *m, double X0[6], int vento)
{
    municao = m;

    // Posição
    X[0] = X0[0];
    X[1] = X0[1];
    X[2] = X0[2];

    // Velocidade
    X[3] = X0[3];
    X[4] = X0[4];
    X[5] = X0[5];

    // Forças
    F[0] =  m->massa()*vento;        // Efeito do vento
    F[1] =  0.;
    F[2] = -m->massa()*GRAVIDADE;    // Efeito da gravidade
}

/**
 * Valor da derivada do i-ésima variável de estado,
 * no instante atual. O tempo foi desprezado porque
 * não há nenhuma grandeza que dependa do tempo.
 */
double Projetil::derivada(int i)
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
        return F[i - 3]/municao->massa();
    }
}


/**
 * atualizar_posicao()
 * Usa o método de integração de Euler para atualizar as variáveis de estado
 */
void Projetil::atualizar_posicao()
{
    for (int i = 0; i < 6; i++)
    {
        X[i] += derivada(i) * DT;
    }
}


/**
 * atingiu_obstaculo()
 * Retorna true se o projétil atingiu um obstâculo: o solo ou algum tanque.
 */
bool Projetil::atingiu_obstaculo()
{
    // Verifica se o projétil atingiu o solo
    bool atingiu = (X[2] - mundo.cenario->z_solo(X[0], X[1])) <= RAIO_PROJETIL;

    // Verifica se o projétil atingiu algum jogador
    for (int i = 0; i < mundo.n_jogadores && !atingiu; i++)
    {
        atingiu = atingiu || mundo.jogadores[i]->atingiu(X);
    }
    return atingiu;
}

/**
 * Desenha o projétil conforme modelo definido pela munição.
 * Translada o desenho para a localização do projétil.
 */
void Projetil::desenhar()
{
    // Transladar o projétil e alinhá-lo com o vetor velocidade.
    // Primeiro normalizar o vetor velocidade
    const double V = sqrt(X[3]*X[3] + X[4]*X[4] + X[5]*X[5]);
    const double vetorV[3] = {X[3]/V, X[4]/V, X[5]/V};

    // Agora encontrar o ângulo entre o eixo X do projétil (longitudinal) e o
    // vetor velocidade
    const double frente[3] = {1, 0, 0};
    double eixo[3] = {0};
    aux::prod_vetorial(frente, vetorV, eixo);
    double angulo = acos(aux::prod_escalar(frente, vetorV)) * 180/PI;

    // Desenha o projétil
    glPushMatrix();
    glTranslated(X[0], X[1], X[2]);
    glRotated(angulo, eixo[0], eixo[1], eixo[2]);
    municao->desenhar();
    glPopMatrix();
}


/**
 * detonar()
 * Produz a explosão do projétil na posição atual
 */
Explosao *Projetil::detonar()
{
    return municao->detonar(X);
}
