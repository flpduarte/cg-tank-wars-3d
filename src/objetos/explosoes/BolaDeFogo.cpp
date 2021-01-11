//
// Created by Felipe on 10/01/2021.
//
#include <GL/gl.h>
#include <cmath>
#include <objetos/explosoes/BolaDeFogo.h>
#include <graphics/cor.h>
#include <constantes.hpp>
#include <objetos3D.hpp>

/**
 * BolaDeFogo
 * Explosão que provoca danos aos outros tanques.
 *
 * Efeito de explosão: exibe na tela o efeito de explosão a partir do epicentro dado.
 * Provoca danos nos tanques conforme modelo abaixo.
 *
 * Modelo de dano:
 *
 * 0                0.9R     1,25R
 * +-----------------|--------|------------>
 * Raio de explosão  | Raio de dano
 * Tanques dentro    | Tanques aqui sofrem dano parcial; cai linearmente
 * deste raioProjetil sofrem | com a distância a partir do raioProjetil de explosão.
 * 100% de dano      | Raio de dano = aprox. 125% do raioProjetil de explosão
 * configurado como  | (configurado como a constante FRACAO_EFEITO_COLATERAL)
 * FRACAO_RAIO_DANO
 */

BolaDeFogo::BolaDeFogo(const double epicentro[3], double r): raio(r), t(0), finalizado(false), raio_atual(0)
{
    this->epicentro[0] = epicentro[0];
    this->epicentro[1] = epicentro[1];
    this->epicentro[2] = epicentro[2];
    cor[0] = 1.0;
    cor[1] = 1.0;
    cor[2] = 1.0;
    cor[3] = 1.0;
    frame_intervalos = (int) (10. * raio/RAIO_INCINERADOR);

    // Cria uma fonte de luz no local da explosão
    glLightfv(GL_LIGHT1, GL_POSITION, (GLfloat *) epicentro);
    glEnable(GL_LIGHT1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, ATENUACAO_QUADRATICA);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 100.0);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2);
}

BolaDeFogo::~BolaDeFogo()
{
    glDisable(GL_LIGHT1);
}

/**
 * Retorna o número de homens de dano considerando um tanque na posição dada.
 * Usa o modelo definido nos comentários acima.
 */
int BolaDeFogo::dano(double pos[3])
{
    // Se o tanque estiver dentro do raioProjetil de explosão, causar dano 100%
    double d = distancia(pos, epicentro);
    if (d < FRACAO_RAIO_DANO*raio)
    {
        return 100;
    }

    // Dano cai linearmente até FRACAO_EFEITO_COLATERAL
    else if (d < FRACAO_EFEITO_COLATERAL * raio)
    {
        return 100 * (FRACAO_EFEITO_COLATERAL * raio - d) / (FRACAO_EFEITO_COLATERAL * raio - FRACAO_RAIO_DANO * raio);
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
bool BolaDeFogo::proximo_frame()
{
    // Primeira parte: Aumenta raioProjetil atual até chegar no raioProjetil máximo
    if (t <= frame_intervalos)
    {
        this->cor[2] = 1. - t/(2.*frame_intervalos);
        raio_atual = raio * (float)t/frame_intervalos;
    }

    // Segunda parte: muda a corBase para vermelho
    else if (t <= 3*frame_intervalos)
    {
        this->cor[1] = 1.  - (t - frame_intervalos)/(2. * frame_intervalos);
        this->cor[2] = 1.  - t/(2. * frame_intervalos);
    }

    // Terceira parte: muda a corBase para preto
    else if (t <= 4*frame_intervalos)
    {
        this->cor[0] = 1. - (t - (3. * frame_intervalos))/(frame_intervalos);
    }

    // Final: fonte de luz se torna escura.
    else
    {
        finalizado = true;
    }

    float cor_sombra[] = {
            (float) 0.5 * this->cor[0],
            (float) 0.5 * this->cor[1],
            (float) 0.5 * this->cor[2],
            (float) 0.5 * this->cor[3]
    };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, this->cor);
    glLightfv(GL_LIGHT1, GL_AMBIENT, cor_sombra);

    t++;
    return !finalizado;
}

/**
 * Desenha a explosão como uma bola de fogo no local do epicentro!
 */
void BolaDeFogo::desenhar()
{
    // Configura intensidade da fonte de luz
    float sombra[] = {FRACAO_SOMBRA * cor[0], FRACAO_SOMBRA * cor[1], FRACAO_SOMBRA * cor[2], FRACAO_SOMBRA * cor[3]};
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
 * distancia()
 * Função auxiliar que retorna a distância euclidiana entre dois pontos dados.
 */
double BolaDeFogo::distancia(double p1[3], double p2[3])
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}


/* Bolas de fogo pré-definidas */

/**
 * Incinerador: Armamento básico
 */
BolaDeFogo *BolaDeFogo::ExplosaoIncinerador(const double *epicentro) {
    return new BolaDeFogo(epicentro, RAIO_INCINERADOR);
}

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
BolaDeFogo *BolaDeFogo::ExplosaoIncineradorMark2(const double *epicentro) {
    return new BolaDeFogo(epicentro, 2 * RAIO_INCINERADOR);
}

/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
BolaDeFogo *BolaDeFogo::Explosao20KilotonNuke(const double *epicentro) {
    return new BolaDeFogo(epicentro, 4 * RAIO_INCINERADOR);
}

/**
 * Bomba 5 Megatons: Dobro do raioProjetil da de 20 kilotons, a arma mais forte!
 */
BolaDeFogo *BolaDeFogo::Explosao5MegatonNuke(const double *epicentro) {
    return new BolaDeFogo(epicentro, 8 * RAIO_INCINERADOR);
}
