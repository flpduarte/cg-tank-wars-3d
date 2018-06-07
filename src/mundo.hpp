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
 * Define a classe Mundo e outros dados associados.
 *
 */
#ifndef MUNDO_HPP
#define MUNDO_HPP

#include "constantes.hpp"
#include "jogador.hpp"
#include "menu.hpp"

/**
 * Mundo: Contém as variáveis de estado do mundo tais como tela atual, no. de
 * jogadores, etc.
 */
class Mundo
{
private:
    // Menu da tela principal pré-alocada, pois nunca muda. Além disso, utiliza
    // as propriedades da própria classe Mundo
    Menu  menu_principal;
    void configurar_menu_principal();

public:
    // Lista de jogadores. Só estarão ativos os jogadores de 0 a n_jogadores - 1
    Jogador *jogadores[MAX_JOGADORES];



    // configurações do jogo
    unsigned int n_jogadores;    // 2, ..., MAX_JOGADORES <= 10
    unsigned int n_rodadas;      // > 0

    // estado atual do mundo
    Tela tela_atual;
    unsigned int rodada_atual;   // 1, 2, ..., n_rodadas

    // Construtor e destrutor
    Mundo();
    ~Mundo();

    // Métodos que transicionam de uma tela para outra e realizam o loop do jogo
    void tela_inicial();        // Vai para a tela inicial
    void escolher_jogadores();  // Tela inicial -> Escolha jogadores
    void inicia_jogo();         // Escolha jogadores -> jogo
    void inicia_rodada();       // Inicia o loop de uma rodada_atual
    void resultado_parcial(int);// Vai para TELA_RESULTADO_PARCIAL e exibe placares. Recebe o n° do vencedor da última rodada
    void compras();
};

#endif
