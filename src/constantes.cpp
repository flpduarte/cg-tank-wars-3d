/**
 * constantes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa a função definir_cor() do namespace cor.
 */
#include <cstring>
#include "constantes.hpp"

void cor::definir_cor(float *dest, const float *origem)
{
    //memcpy(dest, origem, 4*sizeof(float));
    for (int i = 0; i < 4; i++)
    {
        dest[i] = origem[i];
    }
}
