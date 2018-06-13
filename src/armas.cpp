/**
 * armas.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa cada tipo de munição declarada em armas.hpp
 */
#include <iostream>
#include "constantes.hpp"
#include "armas.hpp"

/**
 * Incinerador: Armamento básico
 */
Incinerador::Incinerador()
{
    this->r_explosao = RAIO_INCINERADOR;
}
int Incinerador::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
IncineradorM2::IncineradorM2()
{
    this->r_explosao = 2*RAIO_INCINERADOR;
}
int IncineradorM2::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
Bomba20Kilotons::Bomba20Kilotons()
{
    this->r_explosao = 4*RAIO_INCINERADOR;
}
int Bomba20Kilotons::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Bomba 5 Megatons: Dobro do raio da de 20 kilotons, a arma mais forte!
 */
Bomba5Megatons::Bomba5Megatons()
{
    this->r_explosao = 8*RAIO_INCINERADOR;
}
int Bomba5Megatons::raio_explosao()
{
    return this->r_explosao;
}
