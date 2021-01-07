/**
 * objetos2D.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
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
float desenharTextoCentralizado(const std::string& str, const float altura, void *font, const float *cor);
float texto_alinhado_direita(const std::string&, const float, void *, const float [4]);
void desenhar_borda(const unsigned int largura, const unsigned int altura, const float cor[4]);
#endif
