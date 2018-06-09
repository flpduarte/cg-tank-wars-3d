/**
 * interacoes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Define as funções necessárias pelo OpenGL para realizar:
 * - Interações com Teclado - teclas normais e especiais
 * - Interação com o Mouse (se houver)
 * - Função principal de exibição
 * - Função de animação, se necessária.
 */
#ifndef INTERACOES_HPP
#define INTERACOES_HPP

void interacao_teclado(unsigned char, int, int);
void interacao_teclas_especiais(int, int, int);
void interacao_mouse(int, int, int, int);
void funcao_exibicao();

#endif
