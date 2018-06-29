/**
 * terreno.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Declara a classe Terreno: armazena as informações sobre o terreno:
 * coordenadas e vetores normais, bem como as operações realizadas
 * sobre o terreno.
 *
 */
#ifndef TERRENO_HPP
#define TERRENO_HPP

#include <GL/glut.h>
#include "auxiliares.hpp"

class Terreno
{
    /* Constantes */
    const double XMIN =   0.0;
    const double XMAX = 100.0;
    const double YMIN = -20.0;
    const double YMAX =  20.0;
    const double ZMIN =   0.0;
    const double ZMAX =  40.0;
    const double REFINAMENTO_MALHA = 2.0;

    /* Alturas minima e máxima do terreno, em termos de fração de (ZMAX - ZMIN). */
    const double ALTURA_MINIMA = 0.30;
    const double ALTURA_MAXIMA = 0.70;

    /* Características do terreno */
    const GLfloat COR_TERRENO[4] = {0.2, 0.5, 0.2, 1};
    const GLfloat COR_BORDA[4]   = {0.25, 0.125, 0, 1};

    /* Definição do número de pontos da malha - para desenhar o relevo */
    /* Assume-se que (XMAX - XMIN) e (YMAX - YMIN) são divisíveis por REFINAMENTO_MALHA.*/
    const int NMALHA_X  = (XMAX - XMIN) / REFINAMENTO_MALHA + 1;
    const int NMALHA_Y  = (YMAX - YMIN) / REFINAMENTO_MALHA + 1;

    /* --- Propriedades --- */
    /*
    Mapa de Alturas: É uma matriz com as seguintes características:
   - dimensões: NMALHA_X x NMALHA_Y, constantes determinadas acima
   - elementos: vetor float, com as coordenadas de mundo do solo naquele ponto: (x, y, z)

    Associação entre elementos da matriz e suas respectivas coordenadas do mundo:

    Malha[      0     ][      0     ] --> (XMIN, YMIN)
    Malha[NMALHA_X - 1][NMALHA_Y - 1] --> (XMAX, YMAX)

    O passo em cada eixo, em coordenadas do mundo, é igual à constante REFINAMENTO_MALHA.
    x = XMIN + i*REFINAMENTO_MALHA, i = 0, 1, ..., NMALHA_X - 1.
    y = YMIN + j*REFINAMENTO_MALHA, j = 0, 1, ..., NMALHA_Y - 1.

    Expressoes inversas:
    i = (x - XMIN)/REFINAMENTO_MALHA
    j = (x - YMIN)/REFINAMENTO_MALHA
    */
    GLfloat ***mapa;	    // matriz mapa de alturas
    GLfloat ***normais;   // matriz de vetores normais

    /* Métodos Públicos */
public:
    Terreno();
    ~Terreno();
    void desenhar();
    double z(double x, double y);           // retorna a altura no ponto (x, y)
    GLfloat *normal(double x, double y);     // Retorna o vetor normal ao terreno em (x, y)

    /* Métodos protegidos */
protected:
    void gerar_relevo();
    void calcular_vetores_normais();
    void insere_vertice(int, int);
};

#endif
