/**
 * objetos2D.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara funções que desenham objetos 2D na tela. É utilizada
 * principalmente pelos Menus.
 *
 */
#ifndef OBJETOS2D_HPP
#define OBJETOS2D_HPP
#include <string>

void desenhar_string(std::string str, float altura, void *font, float cor[3]);
void desenhar_borda(unsigned int largura, unsigned int altura, float cor[3]);
float largura_string(std::string str, float altura, void *font);

#endif
