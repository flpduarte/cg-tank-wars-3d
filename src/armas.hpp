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

/* ------------------------- */
/* Funções auxiliares        */

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

#endif
