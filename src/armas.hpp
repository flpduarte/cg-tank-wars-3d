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
 * Declara as classes para cada uma das municoes do jogo, bem como uma lista
 * de armamentos existente.
 *
 */
#ifndef ARMAS_HPP
#define ARMAS_HPP

#include <array>
#include "municao.hpp"

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
    Municao *arma;
    int qtd;

    MunicaoEQtd();                  // Cria um elemento vazio
    MunicaoEQtd(Municao *);         // Armazena a munição e a *quantidade por lote*
    MunicaoEQtd(Municao *, int);    // Armazena a munição e a quantidade especificada

    /**
     * Define operador = para uso com MunicaoEQtd
     */
    void operator=(MunicaoEQtd referencia)
    {
        this->arma = referencia.arma;
        this->qtd  = referencia.qtd;
    }
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
    Municao *arma_atual();      // retorna a arma atual
    int qtd_atual();            // retorna a qtd de tiros da arma atual

    // Alteração da qtd de munição
    void adicionar_lote(int, int);      // Adiciona munição à arma escolhida (ao comprar um armamento)
    void remover_lote(int, int);        // Remove um lote de tiros (ao desfazer uma compra)
    void decrementa_municao();          // Decrementa 1 da qtd de tiros da arma atual
    void condicao_inicial();            // Restaura a lista para a condição de início de jogo'
                                        // (qtd padrão de tiros)
};

/**
 * Cria a lista global de armamentos
 */
std::array <Municao *, N_ARMAMENTOS> *criar_lista_armamentos();

/**
 * Incinerador: Armamento básico
 */
class Incinerador : public MunicaoExplosiva
{
private:
    int r_explosao;
protected:
    int raio_explosao();
public:
    Incinerador();
};

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
class IncineradorM2 : public MunicaoExplosiva
{
private:
    int r_explosao;
protected:
    int raio_explosao();
public:
    IncineradorM2();
};

/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
class Bomba20Kilotons : public MunicaoExplosiva
{
private:
    int r_explosao;
protected:
    int raio_explosao();
public:
    Bomba20Kilotons();
};

/**
 * Bomba 5 Megatons: Dobro do raio da de 20 kilotons, a arma mais forte!
 */
class Bomba5Megatons : public MunicaoExplosiva
{
private:
    int r_explosao;
protected:
    int raio_explosao();
public:
    Bomba5Megatons();
};

/* --- Funções --- */
void criar_lista_global_armamentos();

#endif
