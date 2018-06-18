/**
 * jogador.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções não abstratas da classe Municao e da classe
 * MunicaoExplosiva.
 */

/* Bibliotecas */
#include <GL/glut.h>
#include "constantes.hpp"
#include "municao.hpp"
#include "explosoes.hpp"
#include "objetos3D.hpp"


/* Implementação das funções da classe MunicaoExplosiva */
/**
 * Construtor da MunicaoExplosiva define apenas a sua massa.
 * É igual para todas as munições.
 */
MunicaoExplosiva::MunicaoExplosiva()
{
    this->m = MASSA_MUNICAO;
}

/**
 * Desenha uma munição padrão: uma esfera relativamente brilhosa
 * e cinza.
 *
 * Classes filhas podem implementar seus próprios desenhos, que subs-
 * tituirão esta função.
 */
void MunicaoExplosiva::desenhar()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, COR_PROJETIL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_PROJETIL);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_PROJETIL);

    desenhar_esfera(RAIO_PROJETIL);
}

/**
 * detonar(): Executa a função que produz o efeito de explosão na posição
 * atual do armamento.
 */
void MunicaoExplosiva::detonar(double pos[3])
{
    efeito_explosao(pos, this->raio_explosao());
}
