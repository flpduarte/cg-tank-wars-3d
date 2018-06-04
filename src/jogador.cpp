/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa os métodos da classe Jogador.
 *
 */
#include <string>
#include "armas.hpp"
#include "jogador.hpp"

using namespace std;
void definir_cor(float *, const int);     // função auxiliar para definir a cor do tanque

/**
 * Cria um novo jogador. A cor do jogador é definida pelo seu índice i.
 */
Jogador::Jogador(int i)
{
    // define a cor do tanque:
    definir_cor(this->cor, i);
    this->nome = "Jogador " + to_string(i);
    this->pontos = 0;
    this->dolares = 0;
    this->lista_municoes = nova_lista_municoes();
    
    this->homens = 100;
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->angulo = 90;
    this->potencia = 200;
}


/**
 * Define a cor do tanque de acordo com o número do jogador.
 * A definição da cor segue a mesma sequência que no Tank Wars original.
 * A alteração da cor é realizada por referência.
 */
void definir_cor(float *cor, const int i)
{
    switch (i)
    {
        case 1:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.;
        break;

        case 2:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 3:
        cor[0] = 0.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 4:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 5:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 6:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 7:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 8:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.;
        break;

        case 9:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.5;
        break;

        case 10:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.5;
        break;
    }
}
