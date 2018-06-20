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

float desenhar_string(std::string str, const float altura, void *font, const float [4]);
float largura_string(std::string str, const float altura, void *font);
float texto_centralizado(std::string, const float, void *, const float [4]);
float texto_alinhado_direita(std::string, const float, void *, const float [4]);
void desenhar_borda(const unsigned int largura, const unsigned int altura, const float cor[4]);
#endif
