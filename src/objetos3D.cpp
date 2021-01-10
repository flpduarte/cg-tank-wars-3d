/**
 * objetos3D.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções que desenham os objetos 3D na tela. Objetos incluem
 * tanques, projéteis e explosões.
 *
 * Todos os objetos são desenhados na origem. As estruturas de dados que chamam
 * as funções daqui posteriormente as transladam para a sua devida localização
 * no mundo.
 */
#include <GL/glut.h>
#include <cmath>
#include <graphics/cor.h>
#include <auxiliar/auxiliares.hpp>
#include <constantes.hpp>
#include <objetos3D.hpp>
/* Constantes */
const int NPONTOS = 50;                                 // para desenhar superfícies curvas


/* Constantes usados para desenhar objetos 3D */
const float COR_ESTEIRA[]       = {0.3, 0.3, 0.3, 1};
const float SPECULAR_ESTEIRA[4] = {0.75, 0.75, 0.75, 1};// corBase specular da esteira
const float BRILHO_ESTEIRA      = 48.0f;                // constante usado com GL_SHININESS

const float SPECULAR_TANQUE[4]  = {0.4, 0.4, 0.4, 1};
const float BRILHO_TANQUE       = 32.0f;


/**
 * Desenha um tanque individual. O
 * O tanque ocupa um quadrado 1 x 1. Após desenhar o tanque, ajustar seu tamanho
 * usando glScalef().
 *
 * Origem do tanque: centro do tanque, face inferior.
 * Ele é posicionado no mundo posteriormente, por meio de translações e rotações.
 *
 * Assume que a matriz ativa é a MODELVIEW.
 *
 * - corBase: corBase "real" do jogador - já corrigido pelo número de homens
 * - anguloCanhao: Ângulo
 *
 * Nota: o canhão não é desenhado por esta função. Deve ser desenhado posterior-
 * mente, após o posicionamento do corpo do tanque no mundo.
 */
void desenhar_tanque(const GLfloat *cor)
{
    // Desenha esteiras esquerda e direita
    glPushMatrix();
    glTranslatef(0, -3/8., 0);
    desenhar_esteira_tanque(cor);
    glTranslatef(0,  3/4., 0);
    desenhar_esteira_tanque(cor);
    glPopMatrix();

    // Desenha corpo do tanque - inclusive semi-espera onde ficará o canhão
    desenhar_corpo_tanque(cor);
}

/**
 * Desenha esteira do tanque. Origem localiza-se no centro da esteira.
 */
void desenhar_esteira_tanque(const GLfloat *cor)
{
    // propriedades de iluminação da esteira
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, COR_ESTEIRA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_ESTEIRA);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_ESTEIRA);

    // face inferior
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-3/8.,  1/8., 0);
    glVertex3f( 3/8.,  1/8., 0);
    glVertex3f( 3/8., -1/8., 0);
    glVertex3f(-3/8., -1/8., 0);

    // Face superior
    glNormal3f(0, 0, 1);
    glVertex3f(-1/2.,  1/8., 1/8.);
    glVertex3f( 1/2.,  1/8., 1/8.);
    glVertex3f( 1/2., -1/8., 1/8.);
    glVertex3f(-1/2., -1/8., 1/8.);

    // Frente
    glNormal3f(-1, 0, -1);
    glVertex3f( 3/8.,  1/8., 0);
    glVertex3f( 1/2.,  1/8., 1/8.);
    glVertex3f( 1/2., -1/8., 1/8.);
    glVertex3f( 3/8., -1/8., 0);

    // Trás
    glNormal3f(1, 0, -1);
    glVertex3f(-1/2.,  1/8., 1/8.);
    glVertex3f(-3/8.,  1/8., 0);
    glVertex3f(-3/8., -1/8., 0);
    glVertex3f(-1/2., -1/8., 1/8.);

    glEnd();

    // Desenhar rodas. Cores determinadas pela função desenhar_roda_tanque
    glPushMatrix();
    glTranslatef(0, 0, 1/16.);
    desenhar_roda_tanque(cor);      // Central
    glTranslatef(-1/4., 0, 0);
    desenhar_roda_tanque(cor);      // traseira
    glTranslatef(1/2., 0, 0);
    desenhar_roda_tanque(cor);      // dianteira
    glPopMatrix();

    // Desenhar "armadura" sobre a esteira. Possui a corBase do tanque
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_TANQUE);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_TANQUE);

    // face esquerda
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(-1/2.,  1/8., 1/8.);
    glVertex3f( 1/2.,  1/8., 1/8.);
    glVertex3f( 3/8.,  1/8., 1/4.);
    glVertex3f(-3/8.,  1/8., 1/4.);
    glEnd();

    // face direita
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(-1/2., -1/8., 1/8.);
    glVertex3f( 1/2., -1/8., 1/8.);
    glVertex3f( 3/8., -1/8., 1/4.);
    glVertex3f(-3/8., -1/8., 1/4.);
    glEnd();

    // face noroeste
    glBegin(GL_QUADS);
    glNormal3f(-.125, 0, 1/8.);
    glVertex3f(-1/2., -1/8., 1/8.);
    glVertex3f(-1/2.,  1/8., 1/8.);
    glVertex3f(-3/8.,  1/8., 1/4.);
    glVertex3f(-3/8., -1/8., 1/4.);

    // face norte
    glNormal3f(0, 0, 1);
    glVertex3f(-3/8., -1/8., 1/4.);
    glVertex3f(-3/8.,  1/8., 1/4.);
    glVertex3f( 3/8.,  1/8., 1/4.);
    glVertex3f( 3/8., -1/8., 1/4.);

    // face nordeste
    glNormal3f(0.125, 0, 1/8.);
    glVertex3f( 3/8., -1/8., 1/4.);
    glVertex3f( 3/8.,  1/8., 1/4.);
    glVertex3f( 1/2.,  1/8., 1/8.);
    glVertex3f( 1/2., -1/8., 1/8.);
    glEnd();
}

/**
 * Desenha o corpo central do tanque. Origem é a mesma do próprio tanque.
 */
void desenhar_corpo_tanque(const GLfloat *cor)
{
    // Ajusta corBase do tanque
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_TANQUE);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_TANQUE);

    // Desenha face lateral esquerda
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(-1.0/4,  1/4., 0.75/4.);
    glVertex3f(-1.5/4,  1/4., 0.5/4.);
    glVertex3f(-1.5/4,  1/4., 0.4/4.);
    glVertex3f(-1.25/4, 1/4., 0.1/4.);
    glVertex3f( 1.25/4, 1/4., 0.1/4.);
    glVertex3f( 1.5/4,  1/4., 0.4/4.);
    glVertex3f( 1.5/4,  1/4., 0.5/4.);
    glVertex3f( 1.0/4,  1/4., 0.75/4.);
    glEnd();

    // face lateral direita
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(-1.0/4,  -1/4., 0.75/4.);
    glVertex3f(-1.5/4,  -1/4., 0.5/4.);
    glVertex3f(-1.5/4,  -1/4., 0.4/4.);
    glVertex3f(-1.25/4, -1/4., 0.1/4.);
    glVertex3f( 1.25/4, -1/4., 0.1/4.);
    glVertex3f( 1.5/4,  -1/4., 0.4/4.);
    glVertex3f( 1.5/4,  -1/4., 0.5/4.);
    glVertex3f( 1.0/4,  -1/4., 0.75/4.);
    glEnd();

    // faces superior, inferior, frontal e traseira

    glBegin(GL_QUADS);

    // Face oeste
    glNormal3f(-1, 0, 0);
    glVertex3f(-1.5/4,  1/4., 0.5/4.);
    glVertex3f(-1.5/4,  1/4., 0.4/4.);
    glVertex3f(-1.5/4, -1/4., 0.4/4.);
    glVertex3f(-1.5/4, -1/4., 0.5/4.);

    // Face Noroeste
    glNormal3f( -0.25, 0, 0.5);
    glVertex3f(-1.5/4,  1/4., 0.5/4.);
    glVertex3f(-1.5/4, -1/4., 0.5/4.);
    glVertex3f(-1.0/4, -1/4., 0.75/4.);
    glVertex3f(-1.0/4,  1/4., 0.75/4.);

    // Face Norte
    glNormal3f(0, 0, 1);
    glVertex3f(-1.0/4, -1/4., 0.75/4.);
    glVertex3f(-1.0/4,  1/4., 0.75/4.);
    glVertex3f( 1.0/4,  1/4., 0.75/4.);
    glVertex3f( 1.0/4, -1/4., 0.75/4.);

    // Face Nordeste
    glNormal3f(0.25, 0, 0.5);
    glVertex3f( 1.0/4, -1/4., 0.75/4.);
    glVertex3f( 1.0/4,  1/4., 0.75/4.);
    glVertex3f( 1.5/4,  1/4., 0.5/4.);
    glVertex3f( 1.5/4, -1/4., 0.5/4.);

    // Face leste
    glNormal3f(1, 0, 0);
    glVertex3f( 1.5/4,  1/4., 0.5/4.);
    glVertex3f( 1.5/4,  1/4., 0.4/4.);
    glVertex3f( 1.5/4, -1/4., 0.4/4.);
    glVertex3f( 1.5/4, -1/4., 0.5/4.);

    // Face Sudeste
    glNormal3f( 0.3, 0, -0.25);
    glVertex3f( 1.5/4,   1/4., 0.4/4.);
    glVertex3f( 1.5/4,  -1/4., 0.4/4.);
    glVertex3f( 1.25/4, -1/4., 0.1/4.);
    glVertex3f( 1.25/4,  1/4., 0.1/4.);

    // Face Sudoeste
    glNormal3f(-0.3, 0, -0.25);
    glVertex3f(-1.5/4,  -1/4., 0.4/4.);
    glVertex3f(-1.25/4, -1/4., 0.1/4.);
    glVertex3f(-1.25/4,  1/4., 0.1/4.);
    glVertex3f(-1.5/4,   1/4., 0.4/4.);

    // Face Sul
    glNormal3f(0, 0, -1);
    glVertex3f(-1.25/4, -1/4., 0.1/4.);
    glVertex3f( 1.25/4, -1/4., 0.1/4.);
    glVertex3f( 1.25/4,  1/4., 0.1/4.);
    glVertex3f(-1.25/4,  1/4., 0.1/4.);
    glEnd();

    // desenha semi-esfera superior
    glPushMatrix();
    glTranslatef(0, 0, 0.75/4.);
    desenhar_esfera(1./4, 0, PI/2);
    glPopMatrix();
}

/**
 * Desenha uma roda do tanque. Usar matrizes de translação para
 * posicioná-la.
 * Origem: centro da roda.
 */
void desenhar_roda_tanque(const GLfloat *cor)
{
    // desenha "pneu"
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, COR_ESTEIRA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor::PRETO);   // sem brilho

    // Face externa
    desenhar_faixa_circular(1/16., 1/4.);    // lado externo

    // laterais do pneu
    // lado esquerdo (positivo y)
    glPushMatrix();
    glTranslatef(0.,  1/8., 0.);
    desenhar_anel(1/20., 1/16.);

    // lado direito (negativo y)
    glTranslatef(0., -1/4., 0.);
    glRotatef(180, 0, 0, 1);            // gira 180° em torno de x
    desenhar_anel(1/20., 1/16.);
    glPopMatrix();

    // desenha parede interna da roda na corBase do tanque
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_TANQUE);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, BRILHO_TANQUE);

    glPushMatrix();
    desenhar_faixa_circular(1/20., 1/4., -1);    // lado interno

    // Faces interiores da roda: sem reflexo specular
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor::PRETO);
    glTranslatef(0.,  1/16., 0.);
    desenhar_circulo(1/20.);
    glTranslatef(0., -1/8., 0.);
    glRotatef(180, 0, 0, 1);            // gira 180° em torno de z
    desenhar_circulo(1/20.);
    glPopMatrix();
}


/**
 * Desenha o canhão como um cilindro em torno do eixo X.
 * Parte do pressuposto que o canhão é desenhado com as características do corpo
 * do tanque, pois foi a última operação realizada.
 * TODO: salvar diâmetro e comprimento do canhâo como uma constante.
 */
void desenhar_canhao()
{
    glPushMatrix();
    glRotated(90, 0, 0, 1);
    glTranslated(0, -.75/2, 0);
    desenhar_faixa_circular(RAIO_CANHAO, COMPR_CANHAO);
    glPopMatrix();
}

/* --- Funções Básicas --- */

/**
 * Desenha um círculo no plano xz.
 * Vetor vetorNormal: (0, 1, 0).
 */
void desenhar_circulo(const GLfloat r)
{
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    for (int i = 0; i < NPONTOS; i++)
    {
        double teta    = i*2*PI/NPONTOS;
        glVertex3f(r*cos(teta), 0, r*sin(teta));
    }
    glEnd();
}

/**
 * Desenha uma faixa circular em torno do eixo y.
 * Os vetores normais das faces é automaticamente determinado.
 * r     = raio da faixa.
 * L     = largura do faixa.
 * sinal = sinal do vetor vetorNormal. -1 = inverte o vetor vetorNormal. Para uso em super-
 * fícies internas.
 */
void desenhar_faixa_circular(const GLfloat r, const GLfloat L)
{
    desenhar_faixa_circular(r, L, 1);
}
void desenhar_faixa_circular(const GLfloat r, const GLfloat L, int sinal)
{
    if (sinal < 0) sinal = -1;
    else sinal = 1;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= NPONTOS; i++)  // <= para fechar a circunferência.
    {
        double teta    = i*2*PI/NPONTOS;
        glNormal3f(sinal*cos(teta), 0, sinal*sin(teta));         // vetor vetorNormal alinhado com a direção radial
        glVertex3f(r*cos(teta), -L/2, r*sin(teta));
        glVertex3f(r*cos(teta),  L/2, r*sin(teta));
    }
    glEnd();
}

/**
 * Desenha um anel em torno do eixo y, com raio mínimo r e raio máximo R.
 * Anel localiza-se no plano XZ.
 * Vetor vetorNormal: (0, 1, 0) (direção positiva de y).
 */
void desenhar_anel(const GLfloat r, const GLfloat R)
{
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, 1, 0);
    for (int i = 0; i <= NPONTOS; i++)  // <= para fechar a circunferência.
    {
        double teta    = 2*PI * i/NPONTOS;
        glVertex3f(r*cos(teta), 0, r*sin(teta));
        glVertex3f(R*cos(teta),  0, R*sin(teta));
    }
    glEnd();
}

/**
 * Desenha uma esfera de raio r e centrada na origem.
 * Entrada apenas r: desenha a esfera inteira.
 * Entradas r, t0 e tf: Desenha latitudes [t0, tf].
 */
void desenhar_esfera(GLfloat r)
{
    desenhar_esfera(r, -PI/2, PI/2);
}
void desenhar_esfera(GLfloat r, GLfloat t0, GLfloat tf)
{
    // teta: latitude. Varia de -pi/2 a +pi/2.
    // phi: longitude. Varia de 0 a +2pi.
    const GLfloat deltaTeta = tf - t0;
    const GLfloat deltaPhi  = 2*PI - 0;
    for (int i = 0; i < NPONTOS; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        float teta0 = t0 + deltaTeta * i/NPONTOS;   // i
        float teta1 = teta0 + deltaTeta/NPONTOS;    // i + 1
        for (int j = 0; j <= NPONTOS; j++)
        {
            float phi0 = deltaPhi * j/NPONTOS;
            glNormal3f(aux::x_esfericas(r, teta0, phi0), aux::y_esfericas(r, teta0, phi0), aux::z_esfericas(r, teta0, phi0));
            glVertex3f(aux::x_esfericas(r, teta0, phi0), aux::y_esfericas(r, teta0, phi0), aux::z_esfericas(r, teta0, phi0));
            glNormal3f(aux::x_esfericas(r, teta1, phi0), aux::y_esfericas(r, teta1, phi0), aux::z_esfericas(r, teta1, phi0));
            glVertex3f(aux::x_esfericas(r, teta1, phi0), aux::y_esfericas(r, teta1, phi0), aux::z_esfericas(r, teta1, phi0));
        }
        glEnd();
    }
}
