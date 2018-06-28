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

const int NUM_TIPOS_MORTE = 1;
const int NUM_VARIACOES_MORTE[] = {4};    // vetor com variações possíveis

class Projetil;
class ListaArmamentos;

/**
 * Cria uma enumeração para tipos de morte do jogador!
 * Obs: por enquanto, só 1 tipo foi implementado (27/06/18)
 */
enum TipoMorte
{
    MELTDOWN = 0
};

/**
 * Jogador: classe que contém todas as informações sobre um jogador atual.
 */
struct Jogador
{
    // Propriedades do tanque
    int njogador;       // Número do jogador: 1, 2, ..., MAX_JOGADORES.
    float cor[4];       // em RGBA
    float cor_alterada[4]; // Cor considerando n. de homens. Atualizada pelo método cor_real()
    std::string nome;

    // Pontuação, dinheiro e armamentos disponíveis
    int vitorias;
    int pontos;
    int dolares;
    ListaArmamentos *lista_armas;    // armazena a lista de armas que o jogador possui

    // Estado atual do tanque
    int homens;
    int angulo;             // em graus. Intervalo: [0, 180]. 0° = positivo eixo X (direita).
    int potencia;
    bool vivo;              // indica se o jogador está vivo ou não, para fins de desenhá-lo no cenário.

    // Formas de animação de morte do tanque.
    // A forma de morrer do tanque será definida já no início da rodada!
    int tipo_morte;   // Tipo de morte
    int variacao_morte;     // Variações entre os tipos de morte.

    // Posicionamento do tanque
    double pos[3];      // posição (x, y, z) do tanque
    double normal[3];   // orientação para cima do tanque. Deve ser unitário.

    // Métodos
    Jogador(int i);
    ~Jogador();
    float *cor_real();
    std::string angulo_texto();             // Retorna o ângulo do tanque em formato de string

    void condicao_inicial();
    void reiniciar();
    void desenhar();
    void posicionar(double nova_pos[3]);    // Posiciona o jogador nas coordenadas dada
    void definir_normal(GLfloat normal[3]); // Define o sentido "para cima" do tanque

    Projetil *atirar(int vento);            // Cria um projétil para o cenário
    bool atingiu(double *X);                // Retorna true se a posição do projétil recebida atinge o jogador atual
    void morrer();                          // Executa a animação de morte do jogador atual.
};

#endif
