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
#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include "armas.hpp"

/**
 * Estrutura MunicaoEQtd: Agrupa uma munição e sua respectiva quantidade,
 * para uso na classe Jogador, ao criar a lista de munições.
 */
struct MunicaoEQtd
{
    TipoMunicao tipo;
    int         qtd;
};

MunicaoEQtd *nova_lista_municoes();
Municao     *obter_objeto_municao(TipoMunicao tipo);

/**
 * Jogador: classe que contém todas as informações sobre um jogador atual.
 */
struct Jogador
{
    // Propriedades do tanque
    int njogador;       // Número do jogador: 1, 2, ..., MAX_JOGADORES.
    float cor[4];       // em RGBA
    std::string nome;

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
    ~Jogador();
};

#endif
