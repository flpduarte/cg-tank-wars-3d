/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Contém as declarações da classe Jogador e outras classes relacionadas.
 *
 */
#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <vector>
#include <queue>
#include <GL/glut.h>
#include <globals.hpp>
#include "Projetil.h"
#include "municao.hpp"

const int NUM_TIPOS_MORTE = 1;
const int NUM_VARIACOES_MORTE[] = {4};    // vetor com variações possíveis

class Projetil;
class ListaArmamentos;

/**
 * Jogador: classe que contém todas as informações sobre um jogador atual.
 */
struct Jogador
{
    // Nome e cor do jogador: 1, 2, ..., MAX_JOGADORES.
    float corBase[4];
    std::string nome;

    // Pontuação, dinheiro e armamentos disponíveis
    int vitorias;
    int pontos;
    int dolares;
    ListaArmamentos *lista_armas;    // armazena a lista de armas que o jogador possui

    // Métodos
    Jogador(int i);
    ~Jogador();

    Municao *atirarArmaAtual();

    void resetar_jogador();                             // Reseta a pontuação e as armas do jogador para a condição de início de partida.
    void preparar_para_jogar();                         // Prepara o jogador para o início da sua vez

};

#endif
