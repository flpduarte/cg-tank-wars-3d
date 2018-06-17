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
 * Implementa as funções que desenham os objetos 3D na tela. Objetos incluem
 * tanques, projéteis e explosões.
 *
 * Todos os objetos são desenhados na origem. As estruturas de dados que chamam
 * as funções daqui posteriormente as transladam para a sua devida localização
 * no mundo.
 */
#include <GL/glut.h>
#include "constantes.hpp"
#include "objetos3D.hpp"

/* Constantes */
#define L_TANQUE 4.0f          // Largura e comprimento do tanque.

/* Constantes usados para desenhar objetos 3D */
const float COR_ESTEIRA[]       = {0.4, 0.4, 0.4, 1};
const float SPECULAR_ESTEIRA[4] = {0.6, 0.6, 0.6, 1};   // cor specular da esteira
const float BRILHO_ESTEIRA      = 64.0f;                // constante usado com GL_SHININESS

// (tanque não será brilhoso
const float COR_ARMA[]          = {0.5, 0.5, 0.5, 1};
const float SPECULAR_ARMA[4]    = {1.0, 1.0, 1.0, 1};   // cor especular
const float BRILHO_ARMA         = 24.0f;                // constante usado com GL_SHININESS

/**
 * Desenha um tanque individual.
 * Origem do tanque: centro do tanque, face inferior.
 * Ele é posicionado no mundo posteriormente, por meio de translações e rotações.
 *
 * Assume que a matriz ativa é a MODELVIEW.
 *
 * - homens: Número de homens no tanque. Se traduz como uma porcentagem
 *   a ser multiplicado pela cor do tanque.
 * - cor: cor do jogador
 * - angulo: Ângulo
 *
 * Nota: o canhão não é desenhado por esta função. Deve ser desenhado posterior-
 * mente, após o posicionamento do corpo do tanque no mundo.
 */
void desenhar_tanque(const GLfloat *cor, int homens)
{
    // Ajusta cor real do tanque
    GLfloat cor_real[4];
    for (int i = 0; i < 4; i++)
        cor_real[i] = (GLfloat) homens * cor[i];

    // Desenha esteira direita
    glPushMatrix();
    glTranslatef(0, 3*L_TANQUE/8, 0);
    desenhar_esteira_tanque(cor_real);
    glPopMatrix();

    // Desenha esteira esquerda
    glPushMatrix();
    glTranslatef(0, -3*L_TANQUE/8, 0);
    desenhar_esteira_tanque(cor_real);
    glPopMatrix();

    // Desenha corpo do tanque - inclusive semi-espera onde ficará o canhão
    desenhar_corpo_tanque(cor_real);
}

/**
 * Desenha esteira do tanque. Origem localiza-se no centro da esteira.
 */
void desenhar_esteira_tanque(const GLfloat *cor)
{
    // desenhar esteira: ambos os lados têm cor cinza médio
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor::CINZA_MEDIO);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor::CINZA_MEDIO);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 1);
    glBegin(GL_QUADS);
}
