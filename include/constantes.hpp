/**
 * constantes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Concentra as constantes e tipos enumerados utilizadas no jogo.
 */
#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

/* Constantes gerais */
#define PI 3.14159265358979

/* Constantes da fonte utilizada nos menus */
//#define FONTE            GLUT_STROKE_MONO_ROMAN
#define FONTE            GLUT_STROKE_ROMAN
#define FONTE_ESPESSURA  2
#define FONTE_ALTURA     152.38
#define FONTE_Y0         33.33

/* Dimensões e posição da janela */
const int JANELA_LARGURA   =  800;
const int JANELA_ALTURA    =  600;
const int JANELA_POSICAO_X =   50;
const int JANELA_POSICAO_Y =  100;
#define   JANELA_TITULO      "Tank Wars 3D"

/* Constantes utilizadas por arma.cpp e armas.cpp */
#define RAIO_INCINERADOR    3.0     // Raio de explosão do incinerador; os outros são baseados nesta - usado em armas.cpp (ok), explosoes.cpp (?) e jogador.cpp (???)

/* Constates que influenciam na velocidade de animação e na sensação do jogo */
#define DT_ANIMACAO         10      // Em ms; intervalo de tempo entre chamadas do glutTimerFunc - cenario.cpp

/* Dimensões de referência para desenhar objetos */
const double TAMANHO_TANQUE     = 3.0;          // fator de escala do canhão
const double COMPR_CANHAO       = 0.75;         // comprimento do canhão, sem aplicar fator de escala
const double RAIO_CANHAO        = 1/32.;



#endif
