/**
 * terreno.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara classes auxiliares para realizar operações matemáticas
 */
#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP
namespace aux
{
    /* Declaração de funções */
    class ParOrdenado;
    class Polinomio;

    /* operações sobre vetores */
    double prod_escalar(const double A[3], const double B[3]);
    double *prod_vetorial(const double A[3], const double B[3], double *res);


    /* conversão de coordenadas esféricas para cartesianas */
    double x_esfericas(double, double, double);
    double y_esfericas(double, double, double);
    double z_esfericas(double, double, double);

    /* Resolução de Sistemas de Equações de 1o grau e polinômios */
    double *solucao_sistema_linear(double **A, double *B, int n);   // retorna a solução de Ax = B.
    double *linha_matriz(double x, int n);
    Polinomio *interpolar(ParOrdenado p[], int n);

    /* Classes e estruturas auxiliares */
    /**
     * ParOrdenado: agrupa um par de coordenadas (x, y).
     */
    struct ParOrdenado
    {
    	double x, y;
    };

    /**
     * Polinomio: implementa uma classe que representa um polinômio. Um polinômio é
     * uma função da forma:
     *
     * P(x) = a0 + a1 x + a2 x^2 + a3 x^3 + ... + an x^n
     *
     * Onde n = 0, 1, 2, ... é o grau do polinômio
            a0, a1, ..., an são os coeficientes do polinômio, com an != 0.
     *
     * - grau        : grau do polinômio.
     * - coeficientes: vetor de coeficientes [a0, a1, ..., an]
     *
     * Métodos:
     * - valor(x)  : retorna o valor de P(x)
     * - derivada(): retorna a derivada dP/dx na forma de um novo polinômio de grau
     *               n - 1.
     */
    class Polinomio
    {
    int grau;

    public:
        double *coeficientes;	// vetor de coeficientes. Possui grau + 1 elementos.

        Polinomio(int);
        Polinomio(int n, double *coef);
        ~Polinomio();

        double valor(double);
        Polinomio *derivada();
        void imprimir();
    };
};
#endif
