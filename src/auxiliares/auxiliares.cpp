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
 * Implementa classes auxiliares para realizar operações matemáticas.
 * NOTA: as funções aqui estão dentro do namespace aux.
 */
#include <cmath>
#include <iostream>
#include "auxiliar/auxiliares.hpp"

/**
 * Retorna o produto escalar entre dois vetores.
 * Ambos devem ter dimensão = 3.
 */
double aux::prod_escalar(const double A[3], const double B[3])
{
	return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
}

/**
 * Salva o resultado do produto vetorial entre dois vetores no vetor res.
 * Ambas os fatores devem ter dimensão = 3.
 *
 * Retorna: o próprio ponteiro res.
 */
double *aux::prod_vetorial(const double A[3], const double B[3], double *res)
{
	res[0] = A[1]*B[2] - A[2]*B[1];
	res[1] = A[2]*B[0] - A[0]*B[2];
	res[2] = A[0]*B[1] - A[1]*B[0];
	return res;
}

/**
 * Convertem coordenadas esféricas para cartesianas.
 *
 * teta: latitude.  [-pi/2, pi/2].  Latitude é o ângulo em relação ao plano XY.
 * phi : longitude. [0, 2pi]        Longitude é o ângulo em relação ao eixo X, rotacionando em torno do eixo z.
 * r   : distância radial.
 */
double aux::x_esfericas(double r, double teta, double phi)
{
	return r*cos(teta)*cos(phi);
}
double aux::y_esfericas(double r, double teta, double phi)
{
	return r*cos(teta)*sin(phi);
}
double aux::z_esfericas(double r, double teta, double phi)
{
	return r*sin(teta);
}

/**
 * solucao_sistema_linear()
 * Retorna um vetor x, solução da equação Ax = B.
 * A: matriz n x n
 * B: vetor  n x 1
 *
 * O vetor x é um vetor novo, alocado no heap. Deve posteriormente ser removido
 * via delete x.
 */
double *aux::solucao_sistema_linear(double **A, double *B, int n)
{
	// Modificar A para se tornar matriz triangular
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double fator = -A[j][i]/A[i][i];
			for (int k = i; k < n; k++)
			{
				A[j][k] += fator*A[i][k];
			}
			B[j] += fator*B[i];
		}
	}

	// Encontrar solução da última linha
	double *x = new double[n]();
	x[n - 1] = B[n - 1]/A[n - 1][n - 1];	// primeira solução

	// demais soluções
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = B[i];
		for (int j = n - 1; j > i; j--)
		{
			x[i] -= A[i][j] * x[j];
		}
		x[i] /= A[i][i];
	}
	return x;
}


/**
 * Double Int -> Vetor
 * Gera uma linha da matriz de coeficientes. Em outras palavras, sendo um
 * polinômio da forma P(x) = a0 + a1 x + a2 x² + ... + an x^n, retorna o vetor
 * [1 x x² x³ ..., x^n].
 *
 * É utilizado pelo método gerar_relevo().
 */
double *aux::linha_matriz(double x, int n)
{
	double *linha = new double[n];
	for (int i = 0; i < n; i++)
	{
		linha[i] = pow(x, i);
	}
	return linha;
}


/**
 * ParOrdenado[] int -> Polinômio
 * Dados um vetor de pares ordenados, retorna o polinômio que passa por esses
 * pontos. Sendo n o número de pontos, o polinômio terá grau n - 1.
 */
aux::Polinomio *aux::interpolar(ParOrdenado p[], int n)
{
	// montar matriz A
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = linha_matriz(p[i].x, n);
	}

	// criar vetor B
	double *B = new double[n];
	for (int i = 0; i < n; i++)
	{
		B[i] = p[i].y;
	}

	// encontrar polinômio cujos coeficientes satisfazem à equação Ax = B.
	return new Polinomio(n - 1, solucao_sistema_linear(A, B, n));
}


/**
 * Construtor 1: cria um polinômio com todos os coeficientes iguais a 1
 */
aux::Polinomio::Polinomio(int n)
{
    grau = n;
    coeficientes = new double[n + 1];
    for (int i = 0; i <= n; i++)
    {
     coeficientes[i] = 1;
    }
}

/**
* Construtor 2: cria um polinômio com coeficientes dados
*/
aux::Polinomio::Polinomio(int n, double *coef): grau(n), coeficientes(coef) {}

/**
 * Imprime o polinômio na tela
 */
void aux::Polinomio::imprimir()
{
    for (int i = 0; i <= grau; i++)
    {
        if (coeficientes[i] == 0)
            continue;

        if (i == 0)
        {
            std::cout << coeficientes[0];
        }
        else if (coeficientes[i] < 0)
        {
            std::cout << " - " << -coeficientes[i] << " x^" << i;
        }
        else
        {
            std::cout << " + " << coeficientes[i] << " x^" << i;
        }
    }
    std::cout << std::endl;
}

/**
 * Retorna o valor do polinômio no ponto x dado.
 */
double aux::Polinomio::valor(double x)
{
    double res = 0;
    for (int i = 0; i <= grau; i++)
    {
        res += coeficientes[i]*pow(x, i);
    }
    return res;
}

/**
 * Retorna um ponteiro para um *Polinômio* correspondente à primeira
 * derivada do Polinônio atual
 */
aux::Polinomio *aux::Polinomio::derivada()
{
    Polinomio *dpdx = new Polinomio(grau - 1);
    for (int i = 1; i <= grau; i++)
    {
        dpdx->coeficientes[i - 1] = i * this->coeficientes[i];
    }
    return dpdx;
}
