/**
 * objetos2D.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções que desenham objetos 2D na tela. É utilizada
 * principalmente pelos Menus.
 *
 */
#include <string>
#include <GL/glut.h>
#include "constantes.hpp"
#include "objetos2D.hpp"

/**
 * Escreve um texto na tela.
 * Entradas:
 * font = fonte do stroke character. Pode ser GLUT_STROKE_ROMAN ou
 *        GLUT_STROKE_MONO_ROMAN.
 * str  = string a ser desenhada.
 * cor  = cor do texto, RGB.
 *
 * Variação vertical do caractere é 119,05 unidades para cima e até
 * 33,33 unidades para baixo.
 * https://www.opengl.org/resources/libraries/glut/spec3/node78.html#SECTION000113000000000000000
 */
void desenhar_string(std::string str, float altura, void *font, float cor[3])
{
    // Translada fonte de forma que a origem vertical seja exatamente no centro
    // da fonte
    glPushMatrix();

    // Realiza operação de escala para ajustar fonte à altura desejada
    float escala = altura/FONTE_ALTURA;
    glTranslatef(0, (33.33 - FONTE_ALTURA)/2*escala, 0);
    glScalef(escala, escala, escala);

    // Escreve o texto
    glColor3fv(cor);
    glLineWidth(FONTE_ESPESSURA);
    for (std::string::iterator c=str.begin(); c != str.end(); c++)
    {
 	      glutStrokeCharacter(font, *c);
    }

    glPopMatrix();
}

/**
 * Dado um string, retorna seu comprimento total, em pixels.
 * Função utilizada para centralizar texto na tela.
 */
float largura_string(std::string str, float altura, void *font)
{
    int compr = 0;

    // realiza operação de escala para obter o comprimento final da fonte
    float escala = altura/FONTE_ALTURA;

    // Soma as larguras de cada caractere
    for (std::string::iterator c=str.begin(); c != str.end(); c++)
    {
 	      compr += escala*glutStrokeWidth(font, *c);
    }
    return compr;
}

 /**
  * Desenha a borda de um quadro de menu.
  */
void desenhar_borda(unsigned int largura, unsigned int altura, float cor[3])
{
    glColor3fv(cor);
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(largura, 0, 0);
        glVertex3f(largura, altura, 0);
        glVertex3f(0, altura, 0);
    glEnd();
}
