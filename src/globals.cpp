/**
 * globals.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Concentra as declarações de iniciação das variáveis globais. Os arquivos fonte
 * restantes que precisarem utilizar as variáveis globais precisarão apenas
 * incluir o cabeçalho "globals.hpp".
 *
 * Ler Guideline #6 do documento "C++ Header File Guidelines" escrito por Kieras
 * (2015).
 */
#include "globals.hpp"
#include "armas.hpp"

Mundo mundo;
MunicaoEQtd armamentos[N_ARMAMENTOS]; // cria uma lista vazia
