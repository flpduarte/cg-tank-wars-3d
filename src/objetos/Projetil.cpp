//
// Created by Felipe on 09/01/2021.
//

#include <objetos/Projetil.h>
#include <auxiliar/auxiliares.hpp>
#include <cmath>

/**
 * Cria um novo projétil com condições iniciais dadas.
 * A condição inicial - posição e vetor velocidade - é calculada pelo objeto
 * Tanque que lança o projétil.
 */
Projetil::Projetil(Municao *m, Cenario *cenario, const double X0[6]) : municao(m)
{
    // Posição
    X[0] = X0[0];
    X[1] = X0[1];
    X[2] = X0[2];

    // Velocidade
    X[3] = X0[3];
    X[4] = X0[4];
    X[5] = X0[5];

    // Forças
    F[0] =  m->massa() * cenario->getVento();                      // Efeito do vento
    F[1] =  0.;
    F[2] = -m->massa() * cenario->getGravidade();                  // Efeito da gravidade
}

double const *Projetil::getPosicao() const {
    return X;
}

/**
 * atualizar_posicao()
 * Usa o método de integração de Euler para atualizar as variáveis de estado
 */
void Projetil::atualizar_posicao()
{
    for (int i = 0; i < 6; i++)
    {
        X[i] += derivada(i) * DT;
    }
}

/**
 * Desenha o projétil conforme modelo definido pela munição.
 * Translada o desenho para a localização do projétil.
 */
void Projetil::desenhar()
{
    // Transladar o projétil e alinhá-lo com o vetor velocidade.
    // Primeiro normalizar o vetor velocidade
    const double V = sqrt(X[3]*X[3] + X[4]*X[4] + X[5]*X[5]);
    const double vetorV[3] = {X[3]/V, X[4]/V, X[5]/V};

    // Agora encontrar o ângulo entre o eixo X do projétil (longitudinal) e o
    // vetor velocidade
    const double frente[3] = {1, 0, 0};
    double eixo[3] = {0};
    aux::prod_vetorial(frente, vetorV, eixo);
    double angulo = acos(aux::prod_escalar(frente, vetorV)) * 180/PI;

    // Desenha o projétil
    glPushMatrix();
    glTranslated(X[0], X[1], X[2]);
    glRotated(angulo, eixo[0], eixo[1], eixo[2]);
    municao->desenhar();
    glPopMatrix();
}

/**
 * detonar()
 * Produz a explosão do projétil na posição atual
 */
Explosao *Projetil::detonar()
{
    return municao->detonar(X);
}


/**
 * Valor da derivada do i-ésima variável de estado,
 * no instante atual. O tempo foi desprezado porque
 * não há nenhuma grandeza que dependa do tempo.
 */
double Projetil::derivada(int i)
{
    // Derivada da posição = velocidade
    if (i < 3)
    {
        return X[i + 3];
    }
        // Derivada da velocidade = aceleração.
        // Aceleração = Força / Massa.
        // Esta função calcula a aceleração componente por componente.
    else
    {
        return F[i - 3]/municao->massa();
    }
}