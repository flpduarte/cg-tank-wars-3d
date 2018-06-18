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
#include <GL/glut.h>
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
    int angulo;         // em graus. Intervalo: [0, 180]. 0° = positivo eixo X (direita).
    int potencia;

    // Posicionamento do tanque
    double pos[3];      // posição (x, y, z) do tanque
    double normal[3];   // orientação para cima do tanque.

    // Métodos
    Jogador(int i);
    ~Jogador();
    void desenhar();

    void posicionar(double nova_pos[3]);
    void definir_normal(GLfloat normal[3]);
};

#endif
