/**
 * explosoes.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções que realizam os efeito de detonação.
 * Inicialmente conterá somente explosão;
 * No futuro, será incluso aqui a produção de terra (Ball of Dirt).
 */
#include <GL/glut.h>
#include <cmath>
#include <graphics/cor.h>
#include "../include/explosoes.hpp"
#include "../include/constantes.hpp"
#include "../include/objetos3D.hpp"

/**
 * Explosao
 * Classe que representa uma explosão!
 * Especificamente, é responsável por desenhar a animação da explosão,
 * bem como "avisar" à classe Cenario quando a animação encerrar.
 *
 * Efeito de explosão: exibe na tela o efeito de explosão a partir do epicentro
 * dado.
 * Provoca danos nos tanques conforme modelo abaixo.
 *
 * Modelo de dano:
 *
 * 0                0.9R     1,25R
 * +-----------------|--------|------------>
 * Raio de explosão  | Raio de dano
 * Tanques dentro    | Tanques aqui sofrem dano parcial; cai linearmente
 * deste raio sofrem | com a distância a partir do raio de explosão.
 * 100% de dano      | Raio de dano = aprox. 125% do raio de explosão
 * configurado como  | (configurado como a constante FRACAO_EFEITO_COLAT)
 * FRACAO_RAIO_DANO
 */

Explosao::Explosao(double pos[3], double r): raio(r), t(0), finalizado(false), raio_atual(0)
{
    epicentro[0] = pos[0];
    epicentro[1] = pos[1];
    epicentro[2] = pos[2];
    cor[0] = 1.0;
    cor[1] = 1.0;
    cor[2] = 1.0;
    cor[3] = 1.0;
    frame_intervalos = (int) (10. * raio/RAIO_INCINERADOR);

    // Cria uma fonte de luz no local da explosão
    glLightfv(GL_LIGHT1, GL_POSITION, (GLfloat *) epicentro);
    glEnable(GL_LIGHT1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, aten_quadratica);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 100.0);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2);
}

Explosao::~Explosao()
{
    glDisable(GL_LIGHT1);
}

/**
 * Retorna o número de homens de dano considerando um tanque na posição dada.
 * Usa o modelo definido nos comentários acima.
 */
int Explosao::dano(double pos[3])
{
    // Se o tanque estiver dentro do raio de explosão, causar dano 100%
    double d = dist(pos, epicentro);
    if (d < FRACAO_RAIO_DANO*raio)
    {
        return 100;
    }

    // Dano cai linearmente até FRACAO_EFEITO_COLAT
    else if (d < FRACAO_EFEITO_COLAT*raio)
    {
        return 100 * (FRACAO_EFEITO_COLAT*raio - d) / (FRACAO_EFEITO_COLAT*raio - FRACAO_RAIO_DANO*raio);
    }

    // Fora do alcance da explosão
    else
    {
        return 0;
    }
}

/**
 * Modifica as características da Explosão para permitir que ela seja desenhada
 * no cenário.
 */
bool Explosao::proximo_frame()
{
    // Primeira parte: Aumenta raio atual até chegar no raio máximo
    if (t <= frame_intervalos)
    {
        this->cor[2] = 1. - t/(2.*frame_intervalos);
        raio_atual = raio * (float)t/frame_intervalos;
    }

    // Segunda parte: muda a cor para vermelho
    else if (t <= 3*frame_intervalos)
    {
        this->cor[1] = 1.  - (t - frame_intervalos)/(2. * frame_intervalos);
        this->cor[2] = 1.  - t/(2. * frame_intervalos);
    }

    // Terceira parte: muda a cor para preto
    else if (t <= 4*frame_intervalos)
    {
        this->cor[0] = 1. - (t - (3. * frame_intervalos))/(frame_intervalos);
    }

    // Final: fonte de luz se torna escura.
    else
    {
        finalizado = true;
    }

    GLfloat cor_sombra[] = {
        (GLfloat) 0.5*this->cor[0],
        (GLfloat) 0.5*this->cor[1],
        (GLfloat) 0.5*this->cor[2],
        (GLfloat) 0.5*this->cor[3]
    };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, this->cor);
    glLightfv(GL_LIGHT1, GL_AMBIENT, cor_sombra);

    t++;
    return !finalizado;
}


/**
 * Desenha a explosão como uma bola de fogo no local do epicentro!
 */
void Explosao::desenhar()
{
    // Configura intensidade da fonte de luz
    GLfloat sombra[] = {fracao_sombra * cor[0], fracao_sombra * cor[1], fracao_sombra * cor[2], fracao_sombra * cor[3]};
    glLightfv(GL_LIGHT1, GL_AMBIENT, sombra);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cor);

    // Define propriedades do "material" da bola de fogo: preto, mas com emissividade
    // de superfície.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor::PRETO);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor::PRETO);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->cor);

    // Desenha a bola de fogo. Modelado como uma esfera.
    glMatrixMode(GL_MODELVIEW);
    glTranslated(epicentro[0], epicentro[1], epicentro[2]);
    desenhar_esfera(this->raio_atual);

    // Desativa emissão de superfície.
    glMaterialfv(GL_FRONT, GL_EMISSION, cor::PRETO);
}


/**
 * dist()
 * Função auxiliar que retorna a distância euclidiana entre dois pontos dados.
 */
double Explosao::dist(double p1[3], double p2[3])
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}
