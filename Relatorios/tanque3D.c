#include <math.h>
#include <GL/glut.h>
#define PI 3.14159265358979

GLUquadricObj *obj;

int objId = 1;
float angX = 0;
float angY = 0;

void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);       //habilita o teste de profundidade  
    glMatrixMode(GL_PROJECTION);    // Tipo de matriz de transformações
    glLoadIdentity();
    glOrtho(-5,5,-5,5,-5,5);	// muda o sistema de coordenadas em 3D. O padrão era x, y, z = [-1, 1]
	gluLookAt(0, -5, 0,
			  0,  0, 0,
			  0,  0, 1);
	
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
}

void desenha_tank()
{
	// Desenha eixos para ter uma referência.
	// x: vermelho, y: verde, z: azul
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(5, 0, 0);
	
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5, 0);
	
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);
	
	// Grandezas que definem o tanque - transformar em constantes posteriormente
	int NPONTOS = 20;
	int RAIO = 1;
	int ANGULO  = 0;
	GLdouble RAIO_CANHAO  = 0.25;
	GLdouble COMPR_CANHAO = 2*RAIO;
	
	// Desenha semi-esfera
	glBegin(GL_QUADS);
	for (int i = 0; i < NPONTOS; i++)
	{
		// 0 a 360°
		double phi = 2*PI * i/NPONTOS; 
		for (int j = 0; j < NPONTOS; j++)
		{
			// 0 a 90°
			double teta = PI/2 * j/NPONTOS;
			glVertex3f(RAIO*cos(teta)*cos(phi), RAIO*cos(teta)*sin(phi), RAIO*sin(teta));
			glVertex3f(RAIO*cos(teta)*cos(phi + 2*PI/NPONTOS), RAIO*cos(teta)*sin(phi + 2*PI/NPONTOS), RAIO*sin(teta));
			glVertex3f(RAIO*cos(teta + 2*PI/NPONTOS)*cos(phi + 2*PI/NPONTOS), RAIO*cos(teta + 2*PI/NPONTOS)*sin(phi + 2*PI/NPONTOS), RAIO*sin(teta + 2*PI/NPONTOS));
			glVertex3f(RAIO*cos(teta + 2*PI/NPONTOS)*cos(phi), RAIO*cos(teta + 2*PI/NPONTOS)*sin(phi), RAIO*sin(teta + 2*PI/NPONTOS));
		}
	}
	glEnd();
	
	// base da semi-esfera: circunferência de raio = 1
	gluDisk(obj, 0, RAIO, NPONTOS, NPONTOS);
	
	// desenha canhão: cilindro partindo do centro da esfera
	glPushMatrix();
	glRotatef(ANGULO, 0, 1, 0);
	gluCylinder(obj, RAIO_CANHAO, RAIO_CANHAO, COMPR_CANHAO, NPONTOS, NPONTOS);
	glPopMatrix();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
     glColor3f(1.0,1.0,0.0);
	
	 glPushMatrix();			// Empilha a matriz de transformação atual, antes da transformação
     glRotatef(angX,1,0,0);
     glRotatef(angY,0,1,0);
	 
	 desenha_tank();
	 /*
     switch(objId){
        case 1:
           glutWireSphere(3,40,40);
           //glutSolidSphere(3,10,40);
           //glutSolidSphere(radius,slices,stacks);
           break;
        case 2:
           glutWireCube(3);
           //glutSolidCube(size);
           break;
        case 3:
           glutWireCone(3,5,5,5);
           //glutSolidCone(radius,slices,stacks);
           break;
        case 4:
           glutWireTorus(2,4,20,20);         
           //glutSolidTorus(innerRadius,outerRadius,slices,stacks);         
           break;
        case 5:
           glScalef(3,3,3);
           glutWireIcosahedron();
           //glutSolidIcosahedron();
           break;
        case 6:
           glScalef(3,3,3);
           glutWireOctahedron();
           //glutSolidOctahedron();
           break;
        case 7:
           glScalef(3,3,3);
           glutWireTetrahedron();
           //glutSolidTetrahedron();
           break;
        case 8:
           glScalef(3,3,3);
           glutWireDodecahedron();
           //glutSolidDodecahedron();
           break;
        case 9:
           glutWireTeapot(3);
           //glutSolidTeapot(size);
           break;
        case 10:
           gluCylinder(obj,2,4,10,20,20);
           // gluCylinder(quadric object, bottom radius, top radius, height, slices, stacks)
           break;
        case 11:
           gluDisk(obj,2,5,10,10);
           break;
        case 12:
           gluSphere(obj,2,10,10);
           break;
        default:
           break;
     }    
	 */
     glFlush();
	 glPopMatrix(); // restaura a matriz anterior
}
/*
void keyboard(unsigned char key, int x, int y){
     switch (key){
        case '1' :
           objId = 1;
           break ;
        case '2' :
           objId = 2;
           break ;
        case '3' :
           objId = 3;
           break ;
        case '4' :
           objId = 4;
           break ;
        case '5' :
           objId = 5;
           break ;
        case '6' :
           objId = 6;
           break ;
        case '7' :
           objId = 7;
           break ;
        case '8' :
           objId = 8;
           break ;
        case '9' :
           objId = 9;
           break ;
        case 'a' :
           objId = 10;
           break;
        case 'b' :
           objId = 11;
           break;
        case 'c' :
           objId = 12;
           break;
        default:
           break;
     }
     glutPostRedisplay() ;
}
*/
void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Objetos 3D - OpenGL");
     glutDisplayFunc(display);
     //glutKeyboardFunc(keyboard);
     glutSpecialFunc(transformacoes);
     init();
     glutMainLoop();
}