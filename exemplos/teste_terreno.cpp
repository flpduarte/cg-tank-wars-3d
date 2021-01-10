#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "../include/terreno.hpp"
#include "../include/cenario.hpp"
#include "objetos/jogador.hpp"
#include "../include/globals.hpp"

using namespace std;

/* Características da iluminação do sol */
const GLfloat SOMBRA[] = {0.4f, 0.4f, 0.4f, 1.0f};
const GLfloat POSICAO_SOL[] = {-50, 0, 0, 1};
const GLfloat COR_SOL[] = {1.0f, 1.0f, 1.0f,1.0f};

const GLfloat VERDE[]    = {0, 1, 0, 1};
const GLfloat VERMELHO[] = {1, 0, 0, 1};
const GLfloat AZUL[]     = {0, 0, 1, 1};
const GLfloat AMARELO[]  = {1, 1, 0, 1};

/* Constantes da Cãmera */
const double CAMERA_POS[]    = {50, -100, 50};
const double CAMERA_LOOKAT[] = {50, 0, 24};
const double CAMERA_VIEWUP[] = {0, 0, 1};

const float AZUL_CELESTE[] = {0, 0.66796875, 0.8984375, 1.0};

// Cenário: em princípio, definido como um cubo 100 x 100 x 100.
// Posicionar câmera *atrás* do cenário: y = -150. Com isso, posso definir o plano
// de projeção aprox. na fronteira do cenário, fazendo d_near = 50 (50 unidades à frente da câmera).
// Isso permite que se projete a imagem em um plano à frente da câmera.
Camera camera(CAMERA_POS, CAMERA_LOOKAT, CAMERA_VIEWUP);
Terreno terreno;

Jogador jogador1(1);
Jogador jogador2(2);
Jogador jogador3(3);
Jogador jogador4(4);

void init()
{
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //define a cor de fundo
	glClearColor(0.0f, 0.668f, 0.8984f, 1.0f);
	//terreno = new Terreno();
    
    glLightfv(GL_LIGHT0,GL_AMBIENT, SOMBRA); //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL); //contribuição difusa
	glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
	
	// Habilita iluminação
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    camera.posicionar();
	
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade

	
	/* Volume de recorte com projeção perspectiva
	gluPerspective(GLdouble Field of View [deg], GLdouble Clipping Aspect Ratio, GLdouble dist_near, GLdouble dist_far)
	
	onde: - Field of View: ângulo de abertura da câmera, em graus;
	      - Clipping Aspect Ratio: razão largura/altura da janela de recorte;
		  - dist_near    : Distância da câmera ao plano de recorte. Este é o plano de projeção.
		  - dist_far     : Distância da câmera ao plano de recorte mais afastado.
	*/
    gluPerspective(40.0, 1.3333, 50.0, 500.0);

	// Posiciona os tanques
	jogador1.pos[0] = 10;
	jogador1.pos[1] = 0;
	jogador1.pos[2] = terreno.z(10, 0);
	cout << terreno.z(10, 0) << endl;
	jogador1.definir_normal(terreno.normal(10, 0));
	jogador1.angulo = 45;
	jogador1.homens = 12;
	
	jogador2.pos[0] = 37;
	jogador2.pos[1] = 0;
	jogador2.pos[2] = terreno.z(37, 0);
	jogador2.definir_normal(terreno.normal(37, 0));
	cout << terreno.z(40, 0) << endl;
	jogador2.angulo = 75;
	
	jogador3.pos[0] = 64;
	jogador3.pos[1] = 0;
	jogador3.pos[2] = terreno.z(64, 0);
	jogador3.definir_normal(terreno.normal(64, 0));
	cout << terreno.z(64, 0) << endl;
	jogador3.angulo = 90;
	jogador3.homens = 50;
	
	jogador4.pos[0] = 91;
	jogador4.pos[1] = 0;
	jogador4.pos[2] = terreno.z(91, 0);
	jogador4.definir_normal(terreno.normal(91, 0));
	cout << terreno.z(91, 0) << endl;
	jogador4.angulo = 150;
	jogador4.homens = 77;
}

void cube(){
     glColor3f(1.0,0.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
     glColor3f(0.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,0.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
}



void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
	glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
	
	//glDisable(GL_LIGHT0);
	terreno.desenhar();
	
	
	/*
	// Cubos
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, VERMELHO);
	glTranslatef(10, 0, terreno.z(10, 0));
	cube();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(30, 0, terreno.z(30, 0));
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, VERDE);
	cube();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(50, 0, terreno.z(50, 0));
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AZUL);
	cube();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70, 0, terreno.z(70, 0));
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AMARELO);
	cube();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(90, 0, terreno.z(90, 0));
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AMARELO);
	cube();
	glPopMatrix();
	*/
	
	// desenha jogadores
	glEnable(GL_LIGHT0);
	jogador1.desenhar();
	jogador2.desenhar();
	jogador3.desenhar();
	jogador4.desenhar();
	
	glFlush(); //força o desenho das primitivas
	//glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	
    glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(150,50);
    glutInitWindowSize(800,600);
	glutCreateWindow("Teste de terreno");
	glutDisplayFunc(displayFunc);
	//glutTimerFunc(60,timerFunc,1);
	init();
	glutMainLoop();
	return 0;
}