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
#include "armas.hpp"

using namespace std;

/* Função Principal */
int main(int argc, char *argv[])
{
    // Configurações da tela do jogo
    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowPosition(JANELA_POSICAO_X, JANELA_POSICAO_Y);
    glutInitWindowSize(JANELA_LARGURA, JANELA_ALTURA);
	glutCreateWindow(JANELA_TITULO);

    // Configurações que valem para o jogo inteiro
    glEnable(GL_NORMALIZE);
    glClearColor(0, 0, 0, 0);

    // Define interações
    glutKeyboardFunc(interacao_teclado);
    glutSpecialFunc(interacao_teclas_especiais);
    glutMouseFunc(interacao_mouse);
	glutDisplayFunc(funcao_exibicao);

    // animação
    //glutTimerFunc(10,timerFunc,1);

    // Inicia loop do jogo
    //mundo.tela_inicial();
    //mundo.renomear_jogadores();
    mundo.iniciar_jogo();
	glutMainLoop();
    return 0;
}
