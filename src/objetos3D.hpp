/**
 * objetos3D.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara as funções que desenham os objetos 3D na tela. Objetos incluem tanques,
 * projéteis e explosões.
 *
 * Todos os objetos são desenhados na origem. As estruturas de dados que chamam
 * as funções daqui posteriormente as transladam para a sua devida localização
 * no mundo.
 */
#ifndef OBJETOS3D_HPP
#define OBJETOS3D_HPP

#include <GL/glut.h>

/* Funções de desenhar o tanque */
void desenhar_tanque(const GLfloat *cor, int homens);
void desenhar_esteira_tanque(const GLfloat *cor);
void desenhar_corpo_tanque(const GLfloat *cor);
void desenhar_roda_tanque(const GLfloat *cor);

/* Funções básicas */
void desenhar_circulo(const GLfloat r);
void desenhar_faixa_circular(const GLfloat r, const GLfloat L);
void desenhar_faixa_circular(const GLfloat r, const GLfloat L, int sinal);
void desenhar_anel(const GLfloat r, const GLfloat R);
void desenhar_esfera(GLfloat r);
void desenhar_esfera(GLfloat r, GLfloat teta0, GLfloat teta1);
#endif
