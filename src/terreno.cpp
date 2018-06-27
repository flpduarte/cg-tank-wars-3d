/**
 * terreno.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa a classe Terreno: armazena as informações sobre o terreno:
 * coordenadas e vetores normais, bem como as operações realizadas
 * sobre o terreno.
 *
 */
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <GL/glut.h>
#include "auxiliares.hpp"
#include "terreno.hpp"
#include "constantes.hpp"

// Usar namespace aux, pois a classe terreno utiliza muito as funções auxiliares!
using namespace aux;

/**
 * Cria um terreno novo.
 */
Terreno::Terreno()
{
    // Nova semente para gerador de números aleatórios
    srand(time(NULL));		// semente do gerador de números aleatórios

    // Aloca memória para as matrizes de coordenadas (mapa) e de vetores normais
    mapa    = new GLfloat**[NMALHA_X]();
    normais = new GLfloat**[NMALHA_X]();
	for (int i = 0; i < NMALHA_X; i++)
	{
        mapa[i]    = new GLfloat*[NMALHA_Y]();
        normais[i] = new GLfloat*[NMALHA_Y]();
		for (int j = 0; j < NMALHA_Y; j++)
		{
            normais[i][j] = new GLfloat[3]();
            mapa[i][j]    = new GLfloat[3]();
			mapa[i][j][0] = XMIN + i*REFINAMENTO_MALHA;
			mapa[i][j][1] = YMIN + j*REFINAMENTO_MALHA;
		}
	}

    // Gera relevo e calcula os vetores normais à superfície
    gerar_relevo();
	calcular_vetores_normais();
}

/**
 * Libera a memória utilizada pelo terreno
 */
Terreno::~Terreno()
{
    for (int i = 0; i < NMALHA_X; i++)
    {
        for (int j = 0; j < NMALHA_Y; j++)
        {
            delete[] mapa[i][j];
            delete[] normais[i][j];
        }
        delete[] mapa[i];
        delete[] normais[i];
    }
    delete[] mapa;
    delete[] normais;
}


/**
 * Desenha o terreno no cenário, em coordenadas do mundo.
 */
void Terreno::desenhar()
{
	const int nx = NMALHA_X, ny = NMALHA_Y - 1;
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, COR_TERRENO);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor::PRETO);
    
	for (j = 0; j < ny; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i < nx; i++)
		{
			insere_vertice(i, j);
			insere_vertice(i, j + 1);
		}
		glEnd();
	}


	// Desenhar bordas
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COR_BORDA);

	// Borda Sul (y = YMIN)
	glBegin(GL_QUAD_STRIP);
	glNormal3f(0, -1, 0);
	for (i = 0; i < NMALHA_X; i++)
	{
		glVertex3f(mapa[i][0][0], YMIN, ZMIN);
		glVertex3fv(mapa[i][0]);
	}
	glEnd();

	// Borda Norte (y = YMAX)
	glBegin(GL_QUAD_STRIP);
	glNormal3f(0, 1, 0);
	for (i = 0; i < NMALHA_X; i++)
	{
		glVertex3f(mapa[i][NMALHA_Y - 1][0], YMAX, ZMIN);
		glVertex3fv(mapa[i][NMALHA_Y - 1]);
	}
	glEnd();

	// Borda oeste: x = XMIN
	glBegin(GL_QUAD_STRIP);
	glNormal3f(0, -1, 0);
	for (j = 0; j < NMALHA_Y; j++)
	{
		glVertex3f(XMIN, mapa[0][j][1], ZMIN);
		glVertex3fv(mapa[0][j]);
	}
	glEnd();

	// Borda leste: x = XMAX
	glBegin(GL_QUAD_STRIP);
	glNormal3f(0, -1, 0);
	for (j = 0; j < NMALHA_Y; j++)
	{
		glVertex3f(XMAX, mapa[NMALHA_X - 1][j][1], ZMIN);
		glVertex3fv(mapa[NMALHA_X - 1][j]);
	}
	glEnd();
}

/**
 * Retorna a altura do terreno no ponto (x, y) dado.
 */
double Terreno::z(double x, double y)
{
    // Determina os índices i e j da matriz mapa correspondentes às coordenadas x e y
    int i = (int) round( (x - XMIN)/REFINAMENTO_MALHA );
    int j = (int) round( (y - YMIN)/REFINAMENTO_MALHA );

    // Certifica que i e j estão dentro dos limites da matriz
    if (i < 0)
        i = 0;
    else if (i >= NMALHA_X)
        i = NMALHA_X - 1;

    if (j < 0)
        j = 0;
    else if (j >= NMALHA_Y)
        j = NMALHA_Y - 1;

    return mapa[i][j][2];
}

/**
 * Dadas coordenadas (x, y), retorna o vetor normal ao terreno naquele ponto.
 * Por enquanto estou retornando o vetor normal mais próximo. Um refinamento
 * possível é fazer uma interpolação entre os 4 vetores normais próximos na
 * malha.
 */
GLfloat *Terreno::normal(double x, double y)
{
    // Determina os índices i e j da matriz mapa correspondentes às coordenadas x e y
    int i = (int) round( (x - XMIN)/REFINAMENTO_MALHA );
    int j = (int) round( (y - YMIN)/REFINAMENTO_MALHA );

    // Certifica que i e j estão dentro dos limites da matriz
    if (i < 0)
        i = 0;
    else if (i >= NMALHA_X)
        i = NMALHA_X - 1;

    if (j < 0)
        j = 0;
    else if (j >= NMALHA_Y)
        j = NMALHA_Y - 1;

    return normais[i][j];
}

/* ---- Métodos Protegidos ---- */

/**
 * gerar_relevo()
 * Gera elevações no terreno. É chamada ao criar o objeto.
 */
void Terreno::gerar_relevo()
{
	// Gera um polinômio que representa uma curva do relevo ao logo do eixo X
	const double z0 = ZMIN + ALTURA_MINIMA*(ZMAX - ZMIN);	// altura mínima
	const double z1 = ZMIN + ALTURA_MAXIMA*(ZMAX - ZMIN);	// altura maxima

    // Gera coordenadas com alturas aleatórias entre z0 e z1
	ParOrdenado pontos[] = {
		{  0, 0},
		{ 20, z0 + rand() % ((int) (z1 - z0))},
		{ 40, z0 + rand() % ((int) (z1 - z0))},
		{ 60, z0 + rand() % ((int) (z1 - z0))},
		{ 80, z0 + rand() % ((int) (z1 - z0))},
		{100, 0}
	};
	pontos[0].y = pontos[1].y;
	pontos[5].y = pontos[4].y;

    // Interpola as curvas utilizando um polinômio de grau 6
	Polinomio *P = interpolar(pontos, 6);

	// Ajusta z de todos os pontos do mapa para coincidir com o polinômio.
    // A superfície só variará ao longo do eixo X, ou seja, dada uma coordenada
    // x = x0, Z(x0, y1) = Z(z0, y2) para quaisquer y1 e y2.
	for (int i = 0; i < NMALHA_X; i++)
	{
		for (int j = 0; j < NMALHA_Y; j++)
		{
			double z = P->valor(mapa[i][j][0]);
			if (z < 1) z = 1;
			else mapa[i][j][2] = z;
            //std::cout << mapa[i][j][0] << ", " << mapa[i][j][1] << ", " << mapa[i][j][2] << '\n';
		}

	}
}

/**
 * Calcula a matriz de vetores normais a partir do mapa do terreno.
 */
void Terreno::calcular_vetores_normais()
{
	for (int i = 0; i < NMALHA_X; i++)
	{
		for (int j = 0; j < NMALHA_Y; j++)
		{

			// Coordenada x
			if (i == 0)
			{
				// Tratar as bordas
				normais[0][j][0] = -(mapa[1][j][2] - mapa[0][j][2])/(mapa[1][j][0] - mapa[0][j][0]);
			}
			else if (i == NMALHA_X - 1)
			{
				normais[i][j][0] = -(mapa[i][j][2] - mapa[i - 1][j][2])/(mapa[i][j][0] - mapa[i - 1][j][0]);
			}
			else
			{
				normais[i][j][0] = -(mapa[i + 1][j][2] - mapa[i - 1][j][2])/(mapa[i + 1][j][0] - mapa[i - 1][j][0]);
			}

			// Coordenada y
			if (j == 0)
			{
				// Tratar as bordas
				normais[i][j][1] = -(mapa[i][j + 1][2] - mapa[i][j][2])/(mapa[i][j + 1][1] - mapa[i][j][1]);
			}
			else if (j == NMALHA_Y - 1)
			{
				normais[i][j][1] = -(mapa[i][j][2] - mapa[i][j - 1][2])/(mapa[i][j][1] - mapa[i][j - 1][1]);
			}
			else
			{
				normais[i][j][1] = -(mapa[i][j + 1][2] - mapa[i][j - 1][2])/(mapa[i][j + 1][1] - mapa[i][j - 1][1]);
			}

			// Coordenada z
			normais[i][j][2] = 1;

			// Normalizar o vetor normal
			double modulo = sqrt(normais[i][j][0]*normais[i][j][0] + normais[i][j][1]*normais[i][j][1] + normais[i][j][2]*normais[i][j][2]);
			normais[i][j][0] /= modulo;
			normais[i][j][1] /= modulo;
			normais[i][j][2] /= modulo;
		}
	}
}


/**
 * Insere no OpenGL o vértice correspondente ao elemento (i, j) do mapa de alturas.
 * Insere também o vetor normal associado àquele vértice.
 *
 * Variáveis globais utilizadas:
 * mapa
 * normais
 */
void Terreno::insere_vertice(int i, int j)
{
	glNormal3d(normais[i][j][0], normais[i][j][1], normais[i][j][2]);
	glVertex3fv(mapa[i][j]);
}
