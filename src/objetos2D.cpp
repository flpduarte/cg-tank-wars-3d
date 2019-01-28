/**
 * objetos2D.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções que desenham objetos 2D na tela. É utilizada
 * principalmente pelos Menus.
 *
 */
#include <string>
#include <GL/glut.h>
#include "../include/constantes.hpp"
#include "../include/objetos2D.hpp"

/**
 * Escreve um texto na tela, alinhado à esquerda. Retorna a sua largura.
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
float desenhar_string(std::string str, const float altura, void *font, const float cor[5])
{
    // Translada fonte de forma que a origem vertical seja exatamente no centro
    // da fonte
    glPushMatrix();

    // Realiza operação de escala para ajustar fonte à altura desejada
    float largura = 0;
    float escala = altura/FONTE_ALTURA;
    glTranslatef(0, (33.33 - FONTE_ALTURA)/2*escala, 0);
    glScalef(escala, escala, escala);

    // Escreve o texto
    glColor4fv(cor);
    glLineWidth(FONTE_ESPESSURA);
    for (std::string::iterator c=str.begin(); c != str.end(); c++)
    {
 	    glutStrokeCharacter(font, *c);
        largura += escala*glutStrokeWidth(font, *c);
    }

    glPopMatrix();
    return largura;
}

/**
 * Dado um string, retorna seu comprimento total, em pixels.
 * Usado quando se precisa saber do comprimento antes de digitar o texto.
 */
float largura_string(std::string str, const float altura, void *font)
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
 * Imprime um texto centralizado na origem.
 */
float texto_centralizado(std::string str, const float altura, void *font, const float cor[4])
{
    glPushMatrix();
    glTranslatef(-largura_string(str, altura, font) / 2., 0, 0);
    float largura = desenhar_string(str, altura, font, cor);
    glPopMatrix();
    return largura;
}

/**
 * Imprime um texto centralizado na origem.
 */
float texto_alinhado_direita(std::string str, const float altura, void *font, const float cor[4])
{
    glPushMatrix();
    glTranslatef(-largura_string(str, altura, font), 0, 0);
    float largura = desenhar_string(str, altura, font, cor);
    glPopMatrix();
    return largura;
}
