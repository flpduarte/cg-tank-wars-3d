#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "..\src\terreno.hpp"
#include "..\src\cenario.hpp"

using namespace std;

/* Características da iluminação do sol */
const GLfloat SOMBRA[] = {0.6f, 0.6f, 0.6f, 1.0f};
const GLfloat POSICAO_SOL[] = {-150, 50, 200, 1};
const GLfloat COR_SOL[] = {1.0f, 1.0f, 1.0f,1.0f};

/* Constantes da Cãmera */
const double CAMERA_POS[]    = {50, 100, 80};
const double CAMERA_LOOKAT[] = {50, 0, 20};
const double CAMERA_VIEWUP[] = {0, 0, 1};

void imprime_matriz(double **A, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%7.3f   ", A[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void imprime_matriz(double *A, int n)
{
	imprime_matriz(&A, 1, n);
}

void imprime_matriz(double **A, int n)
{
	imprime_matriz(A, n, n);
}

// Cenário: em princípio, definido como um cubo 100 x 100 x 100.
// Posicionar câmera *atrás* do cenário: y = -150. Com isso, posso definir o plano
// de projeção aprox. na fronteira do cenário, fazendo d_near = 50 (50 unidades à frente da câmera).
// Isso permite que se projete a imagem em um plano à frente da câmera.
Camera camera(CAMERA_POS, CAMERA_LOOKAT, CAMERA_VIEWUP);
Terreno terreno;


void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
	//terreno = new Terreno();
    
    //glLightfv(GL_LIGHT0,GL_POSITION,light1_pos); //dene posição da luz
    glLightfv(GL_LIGHT0,GL_AMBIENT, SOMBRA); //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL); //contribuição difusa
	glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
	
	// Habilita iluminação
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	
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
    gluPerspective(45.0, 1.0, 50.0, 500.0); 
	
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    //glViewport(0, 0, 500, 500);
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
	terreno.desenhar();
	
	glPushMatrix();
	glTranslatef(50, 0, terreno.z(50, 0));
	cube(); //desenha um cubo
	glPopMatrix();
	
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