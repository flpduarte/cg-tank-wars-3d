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
 * Declara as classes para cada uma das municoes do jogo, bem como uma lista
 * de armamentos existente.
 *
 */
#ifndef ARMAS_HPP
#define ARMAS_HPP

#include <array>
#include <objetos/armas/Arma.h>

#define N_ARMAMENTOS 4

/**
 * Define tipo enumerado para se referir a um armamento especifico
 */
enum TipoMunicao
{
    INCINERADOR,
    INCINERADORM2,
    BOMBA20KILOTONS,
    BOMBA5MEGATONS
};

/**
 * MunicaoEQtd: um elemento de ListaArmamentos. Armazena uma arma e a
 * quantidade de tiros que o jogador possui.
 */
struct MunicaoEQtd
{
    Arma *arma;
    int qtd;

    MunicaoEQtd();                  // Cria um elemento vazio
    MunicaoEQtd(Arma *);         // Cria elemento com munição e sua *quantidade por lote*

    /**
     * Define operador = para uso com MunicaoEQtd
     */
    void operator=(MunicaoEQtd referencia);
};

/**
 * ListaArmamentos
 * Uma lista de armamentos utilizada pela classe Jogador. Armazena
 * cada munição e a quantidade de tiros.
 */
class ListaArmamentos
{
    //std::array<MunicaoEQtd, N_ARMAMENTOS> lista;
    MunicaoEQtd lista[N_ARMAMENTOS];
    int i_atual;         // arma atualmente selecionada

public:
    ListaArmamentos();      // constroi a lista das armas existentes no jogo

    // Seleção de armamentos
    void selecionar_proxima();  // seleciona próxima arma.
    Arma *arma_atual();      // retorna a arma atual
    int qtd_atual();            // retorna a qtd de tiros da arma atual

    // Alteração da qtd de munição
    void adicionar_lote(int, int);      // Adiciona munição à arma escolhida (ao comprar um armamento)
    void remover_lote(int, int);        // Remove um lote de tiros (ao desfazer uma compra)
    Arma *atirarArmaAtual();       // Decrementa 1 da qtd de tiros da arma atual. Retorna a arma atual.
    void condicao_inicial();            // Restaura a lista para a condição de início de jogo'
                                        // (qtd padrão de tiros)
};


/* --- Funções --- */
void criar_lista_global_armamentos();

#endif
