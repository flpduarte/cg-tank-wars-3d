#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "..\src\jogador.hpp"
#include "..\src\constantes.hpp"

Jogador jogador(8);

void lighting() {
    //define a posição e parâmetros da luz 0
    float position[] = {5.0f, 0.0f, 5.0f, 1.0f};
    float white[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

    //ativando luz ambiente global
    float global_ambient[] = {0.6f, 0.6f, 0.6, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
	glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(3, -5, 1, //posição da câmera
              0.0, 0.0, 1, //para onde a câmera aponta
              0.0, 0.0, 1.); //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
	gluPerspective(75.0, 1.0, 0.1, 100);

    lighting(); //defininido os parâmetros de iluminação
	
	// define normal do jogador
	//jogador.normal[0] = 0.6;
	//jogador.normal[2] = 0.8;
	jogador.angulo = 75;
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //define que a matrix é a a model view
    glMatrixMode(GL_MODELVIEW);
	
	// Propriedade do material da esfera
	float cor[] = {0.5, 0.5, 0.5, 1};
	float white[] = {1.f, 1.f, 1.f, 1.0f};
	float yellow[]= {1.0, 1.0, 0, 1};
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 24.0);
    glutSolidSphere(1.5, 40, 40);
	*/
	
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	//glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
	//desenhar_esfera(0.7, 0, PI/2);
	//glutSolidSphere(0.7, 40, 40);

    //força o desenho das primitivas
	jogador.desenhar();
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
	glutCreateWindow("Viewing 3D - Projecao Perspectiva");
	glutDisplayFunc(displayFunc);
	init();
	glutMainLoop();
	return 0;
}