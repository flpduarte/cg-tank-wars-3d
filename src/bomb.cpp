/**
 * bomb.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Este é o programa principal.
 *
 */

/* Bibliotecas */
#include <iostream>
#include <GL/glut.h>
#include "constantes.hpp"
#include "globals.hpp"
#include "mundo.hpp"
#include "interacoes.hpp"

using namespace std;


int main()
{
    // Inicia janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(JANELA_POSICAO_X, JANELA_POSICAO_Y);
    glutInitWindowSize(JANELA_LARGURA, JANELA_ALTURA);
	glutCreateWindow(JANELA_TITULO);

    // Define interações
    glutKeyboardFunc(interacao_teclado);
    glutSpecialFunc(interacao_teclas_especiais);
    glutMouseFunc(interacao_mouse);
	glutDisplayFunc(funcao_exibicao);

    // animação
    //glutTimerFunc(10,timerFunc,1);

    // Inicia loop do jogo
	glutMainLoop();
}
