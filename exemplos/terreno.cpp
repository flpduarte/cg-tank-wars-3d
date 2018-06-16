#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

using namespace std;

/*
Coordenadas do terreno:

x: [0, 100]
y: [-50, 50]
z: [0, 100]
*/
#define XMIN   0.0
#define XMAX 100.0
#define YMIN -50.0
#define YMAX  50.0
#define ZMIN   0.0
#define ZMAX 60.0
#define REFINAMENTO_MALHA  0.5
#define PASSO_X 	20.0
#define PASSO_Y 	10.0

void imprime_matriz(double **A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5.1f   ", A[i][j]);
		}
		std::cout << std::endl;
	}
}

/* Divisao de x e y para construçao das curvas */
const int NPONTOS_X = (XMAX - XMIN) / PASSO_X + 1;
const int NPONTOS_Y = (YMAX - YMIN) / PASSO_Y + 1;


/* Definição do número de pontos da malha - para desenhar o relevo */
/* Assume-se que (XMAX - XMIN) e (YMAX - YMIN) são divisíveis por REFINAMENTO_MALHA.*/
const int NMALHA_X  = (XMAX - XMIN) / REFINAMENTO_MALHA + 1;
const int NMALHA_Y  = (YMAX - YMIN) / REFINAMENTO_MALHA + 1;

/* Mapa de Alturas: É uma matriz com as seguintes características:
   - dimensões: NMALHA_X x NMALHA_Y, constantes determinadas acima
   - elementos: vetor float, com as coordenadas de mundo do solo naquele ponto: (x, y, z)

Associação entre elementos da matriz e suas respectivas coordenadas do mundo:

Malha[      0     ][      0     ] --> (XMIN, YMIN)
Malha[NMALHA_X - 1][NMALHA_Y - 1] --> (XMAX, YMAX)

O passo em cada eixo, em coordenadas do mundo, é igual à constante REFINAMENTO_MALHA.
x = XMIN + i*REFINAMENTO_MALHA, i = 0, 1, ..., NMALHA_X - 1.
y = YMIN + j*REFINAMENTO_MALHA, j = 0, 1, ..., NMALHA_Y - 1.

Expressoes inversas:
i = (x - XMIN)/REFINAMENTO_MALHA
j = (x - YMIN)/REFINAMENTO_MALHA

*/

int x_para_i(double x)
{
	return (int) round((x - XMIN)/REFINAMENTO_MALHA);
}

int y_para_j(double y)
{
	return (int) round((y - YMIN)/REFINAMENTO_MALHA);
}

GLfloat mapa[NMALHA_X][NMALHA_Y][3]     = {0};	// matriz mapa de alturas
GLfloat normais[NMALHA_X][NMALHA_Y][3] = {0};	// matriz de vetores normais

/**
 * Inicia a matriz mapa: calcula todas as coordenadas x e y; as coordenadas z são
 * inicialmente considerados 0.
 */
void iniciar_mapa()
{
	for (int i = 0; i < NMALHA_X; i++)
	{
		for (int j = 0; j < NMALHA_Y; j++)
		{
			mapa[i][j][0] = XMIN + i*REFINAMENTO_MALHA;
			mapa[i][j][1] = YMIN + j*REFINAMENTO_MALHA;
		}
	}
}

/**
 * Calcula a matriz de vetores normais a partir do mapa do terreno.
 */
void calcular_vetores_normais()
{
	for (int i = 0; i < NMALHA_X; i++)
	{
		for (int j = 0; j < NMALHA_Y; j++)
		{
			// Coordenada x
			if (i == 0)
			{
				// Tratar as bordas
				normais[0][j][0] = -(mapa[1][j][2] - mapa[0][j][2])/(mapa[1][j][0] - mapa[0][j][0]);
			}
			else if (i == NMALHA_X - 1)
			{
				normais[i][j][0] = -(mapa[i][j][2] - mapa[i - 1][j][2])/(mapa[i][j][0] - mapa[i - 1][j][0]);
			}
			else
			{
				normais[i][j][0] = -(mapa[i + 1][j][2] - mapa[i - 1][j][2])/(mapa[i + 1][j][0] - mapa[i - 1][j][0]);
			}
			
			// Coordenada y
			if (j == 0)
			{
				// Tratar as bordas
				normais[i][j][1] = -(mapa[i][j + 1][2] - mapa[i][j][2])/(mapa[i][j + 1][0] - mapa[i][j][0]);
			}
			else if (j == NMALHA_Y - 1)
			{
				normais[i][j][1] = -(mapa[i][j][2] - mapa[i][j - 1][2])/(mapa[i][j][0] - mapa[i][j - 1][0]);
			}
			else
			{
				normais[i][j][1] = -(mapa[i][j + 1][2] - mapa[i][j - 1][2])/(mapa[i][j + 1][0] - mapa[i][j - 1][0]);
			}
			
			// Coordenada z
			normais[i][j][2] = 1;
			
			// Normalizar o vetor normal
			double modulo = sqrt(normais[i][j][0]*normais[i][j][0] + normais[i][j][1]*normais[i][j][1] + normais[i][j][2]*normais[i][j][2]);
			normais[i][j][0] /= modulo;
			normais[i][j][1] /= modulo;
			normais[i][j][2] /= modulo;
		}
	}
}

/** ===================================================== */

/* Funções de Polinômio */
class Polinomio
{
	int grau;
	
	public:
	double *coeficientes;	// vetor de coeficientes. Possui grau + 1 elementos.
	
	/**
	 * Construtor 1: cria um polinômio com todos os coeficientes iguais a 1
	 */
	Polinomio(int n)
	{
		grau = n;
		coeficientes = new double[n + 1];
		for (int i = 0; i <= n; i++)
		{
			coeficientes[i] = 1;
		}
	}
	
	/**
	 * Construtor 2: cria um polinômio com coeficientes dados
	 */
	Polinomio(int n, double *coef): grau(n), coeficientes(coef) {}
	
	
	~Polinomio()
	{
		delete coeficientes;
	}
	
	/**
	 * Retorna o valor do polinômio no ponto x dado.
	 */
	double valor(double x)
	{
		double res = 0;
		for (int i = 0; i <= grau; i++)
		{
			res += coeficientes[i]*pow(x, i);
		}
		return res;
	}
	
	/**
	 * Retorna um ponteiro para um *Polinômio* correspondente à primeira 
	 * derivada do Polinônio atual
	 */
	Polinomio *derivada()
	{
		Polinomio *dpdx = new Polinomio(grau - 1);
		for (int i = 1; i <= grau; i++)
		{
			dpdx->coeficientes[i - 1] = i * this->coeficientes[i];
		}
		return dpdx;
	}
	
	/**
	 * Imprime o polinômio na tela
	 */
	void imprimir()
	{
		for (int i = 0; i <= grau; i++)
		{
			if (coeficientes[i] == 0)
				continue;
			
			if (i == 0)
			{
				std::cout << coeficientes[0];
			}
			else if (coeficientes[i] < 0)
			{
				std::cout << " - " << -coeficientes[i] << " x^" << i;
			}
			else
			{
				std::cout << " + " << coeficientes[i] << " x^" << i;
			}
		}
		std::cout << std::endl;
	}
};

struct ParOrdenado
{
	double x, y;
};

/**
 * Double Int -> Vetor
 * Gera uma linha da matriz de coeficientes. Em outras palavras, sendo um
 * polinômio da forma P(x) = a0 + a1 x + a2 x² + ... + an x^n,
 * retorna o vetor [1 x x² x³ ..., x^n]
 */
double *linha_matriz(double x, int n)
{
	double *linha = new double[n];
	for (int i = 0; i < n; i++)
	{
		linha[i] = pow(x, i);
	}
	return linha;
}

/**
 * solucao_sistema_linear()
 * Retorna um vetor x, solução da equação Ax = B.
 * A: matriz n x n
 * B: vetor  n x 1
 */
double *solucao_sistema_linear(double **A, double *B, int n)
{
	cout << endl;
	
	// Modificar A para se tornar matriz triangular
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double fator = -A[j][i]/A[i][i];
			for (int k = i; k < n; k++)
			{
				A[j][k] += fator*A[i][k];
			}
			B[j] += fator*B[i];
		}
		
		
	}
	
	// Encontrar solução da última linha
	double *x = new double[n]();
	x[n - 1] = B[n - 1]/A[n - 1][n - 1];	// primeira solução
	
	// demais soluções
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = B[i];
		for (int j = n - 1; j > i; j--)
		{
			x[i] -= A[i][j] * x[j];
		}
		x[i] /= A[i][i];
	}
	
	return  x;
}
 
/**
 * ParOrdenado[6] -> Polinômio
 * Dados os valores de z(0), z(20), z(40), z(60), z(80) e z(100),
 * produz um polinômio de 5º grau que passa pelos 6 pontos dados.
 *
 * Função abstraída: deve-se dar um vetor de pares ordenados e o
 * número de pares; o polinômio gerado terá grau n - 1.
 */
Polinomio *encontrar_curva(ParOrdenado p[], int n)
{
	// montar matriz A
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = linha_matriz(p[i].x, n);
	}
	
	// criar vetor B
	double *B = new double[n];
	for (int i = 0; i < n; i++)
	{
		B[i] = p[i].y;
	}
	
	// encontrar polinômio cujos coeficientes satisfazem à equação Ax = B.
	return new Polinomio(n - 1, solucao_sistema_linear(A, B, n));
}


/**
 * gerar_relevo()
 * Gera elevações no terreno.
 */
void gerar_relevo()
{
	const int zmax = (int) ZMAX;
	// inicia o mapa
	iniciar_mapa();
	
	// Gera um polinômio que representa a curva do relevo ao logo do eixo X
	ParOrdenado pontos[] = {
		{  0, 0},
		{ 20, ZMAX/20 + (double) (rand()%(zmax/10*5))},
		{ 40, ZMAX/20 + (double) (rand()%(zmax/10*5))},
		{ 60, ZMAX/20 + (double) (rand()%(zmax/10*5))},
		{ 80, ZMAX/20 + (double) (rand()%(zmax/10*5))},
		{100, 0}
	};
	pontos[0].y = pontos[1].y;
	pontos[5].y = pontos[4].y;
	
	Polinomio *P = encontrar_curva(pontos, 6);
	
	// Ajusta z de todos os pontos do mapa para coincidir com o polinômio
	for (int i = 0; i < NMALHA_X; i++)
	{
		for (int j = 0; j < NMALHA_Y; j++)
		{
			double z = P->valor(mapa[i][j][0]);
			if (z < 1) z = 1;
			else if (z > zmax) z = zmax;
			else mapa[i][j][2] = z;
		}
	}
	
	// Calcular vetores normais
	calcular_vetores_normais();
}

/**
 * Insere no OpenGL o vértice correspondente ao elemento (i, j) do mapa de alturas.
 * Insere também o vetor normal associado àquele vértice.
 *
 * Variáveis globais utilizadas:
 * mapa
 * normais
 */
void insere_vertice(int i, int j)
{
	glNormal3fv(normais[i][j]);
	glVertex3fv(mapa[i][j]);
}

/* Desenha o terreno usando TRIANGLE_STRIP */
void desenhar_terreno()
{
	const int nx = NMALHA_X, ny = NMALHA_Y - 1;
	int i, j;
	double *coordenada = new double[3]();				// variável auxiliar
	
	glColor3f(0, 0.5, 0);
	for (j = 0; j < ny; j++)
	{
		//glBegin(GL_LINES);
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i < nx; i++)
		{
			insere_vertice(i, j);
			insere_vertice(i, j + 1);
		}
		glEnd();
	}
	
	
	// Desenhar lateral
	// Borda Sul (y < 0)
	
	
	//glBegin(GL_QUAD_STRIP);
	glBegin(GL_LINES);
	glColor3f(0.5, 0.25, 0);
	for (i = 0; i < NMALHA_X; i++)
	{
		glVertex3f(mapa[i][0][0], YMIN, ZMIN);
		glVertex3fv(mapa[i][0]);
	}
	glEnd();
	
}



/* Agrupamento das informações da câmera em uma estrutura */
struct Camera
{
	float pos[3];
	float look_at[3];
	float view_up[3];
};

/* Atalho para posicionar câmera */
void posicionar_camera(Camera c)
{
	gluLookAt(c.pos[0], c.pos[1], c.pos[2],
			  c.look_at[0], c.look_at[1], c.look_at[2],
			  c.view_up[0], c.view_up[1], c.view_up[2]);
}

// Cenário: em princípio, definido como um cubo 100 x 100 x 100.
// Posicionar câmera *atrás* do cenário: y = -150. Com isso, posso definir o plano
// de projeção aprox. na fronteira do cenário, fazendo d_near = 50 (50 unidades à frente da câmera).
// Isso permite que se projete a imagem em um plano à frente da câmera.
Camera camera {{50, -50, 100}, {50, 0, 0}, {0, 0, 1}};


void init()
{
	srand(time(NULL));		// raiz do gerador de números aleatórios
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    posicionar_camera(camera);
	
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
	
	// Gerar relevo
	gerar_relevo();

	
	/* Volume de recorte com projeção perspectiva
	gluPerspective(GLdouble Field of View [deg], GLdouble Clipping Aspect Ratio, GLdouble dist_near, GLdouble dist_far)
	
	onde: - Field of View: ângulo de abertura da câmera, em graus;
	      - Clipping Aspect Ratio: razão largura/altura da janela de recorte;
		  - dist_near    : Distância da câmera ao plano de recorte. Este é o plano de projeção.
		  - dist_far     : Distância da câmera ao plano de recorte mais afastado.
	*/
    gluPerspective(60.0, 1.0, 50.0, 500.0); 
	
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    //glViewport(0, 0, 500, 500);


    //imprime as matrized GL_PROJECTION e GL_MODELVIEW
	/*
    printf("M_ortho = \n");
    float matrix[16];
    int i,j;
    glGetFloatv(GL_PROJECTION_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n\nM_wc,vc = \n");
    glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");
	*/
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
	desenhar_terreno();
	
	glPushMatrix();
	glTranslatef(50, 0, mapa[x_para_i(50)][y_para_j(0)][2]);
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
    glutInitWindowSize(500,500);
	glutCreateWindow("Teste de terreno");
	glutDisplayFunc(displayFunc);
	//glutTimerFunc(60,timerFunc,1);
	init();
	glutMainLoop();
	return 0;
}