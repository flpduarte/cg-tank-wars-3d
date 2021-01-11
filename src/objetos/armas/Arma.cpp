/**
 * jogador.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções não abstratas da classe Arma e da classe
 * ArmaExplosiva.
 */

/* Bibliotecas */
#include <GL/glut.h>
#include <objetos/armas/Arma.h>
#include <objetos3D.hpp>

constexpr float Arma::COR_PROJETIL[];
constexpr float Arma::SPECULAR_PROJETIL[];
constexpr float Arma::BRILHO_PROJETIL;
constexpr double Arma::RAIO_PADRAO_PROJETIL;

Arma::Arma(std::string nome, int preco, int qtdPorLote, int qtdInicial, double massaProjetil, double raioProjetil) :
        massaProjetil(massaProjetil),
        raioProjetil(raioProjetil),
        nome(std::move(nome)),
        preco(preco),
        quantidadePorLote(qtdPorLote),
        quantidadeInicial(qtdInicial)
{}

double Arma::getMassaProjetil() const
{
    return massaProjetil;
}

double Arma::getRaioProjetil() const {
    return raioProjetil;
}

/**
 * Desenha um projétil padrão: uma esfera relativamente brilhosa e cinza.
 *
 * Classes filhas podem implementar seus próprios desenhos, que substituirão esta função.
 */
void Arma::desenhar()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, COR_PROJETIL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_PROJETIL);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_PROJETIL);
    desenhar_esfera(raioProjetil);
}

