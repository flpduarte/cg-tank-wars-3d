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
 * Contém as declarações da classe Jogador e outras classes relacionadas.
 *
 */
#include <string>
#include "armas.hpp"
using namespace std;

/**
 * Jogador: classe que contém todas as informações sobre um jogador atual.
 */
struct Jogador
{
    // Propriedades do tanque
    string nome[31];
    float cor[3];       // em RGB

    // Pontuação, dinheiro e armamentos disponíveis
    int pontos;
    int dolares;
    MunicaoEQtd *lista_municoes;

    // Estado atual do tanque
    int homens;
    double pos[3];
    int angulo;
    int potencia;

    // Métodos
    Jogador(int i);
    //void re
};
