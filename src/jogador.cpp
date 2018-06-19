/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa os métodos da classe Jogador.
 *
 */
#include <cmath>
#include <string>
#include <iostream>
#include "jogador.hpp"
#include "globals.hpp"
#include "auxiliares.hpp"
#include "constantes.hpp"
#include "objetos3D.hpp"

void definir_cor(float *, const int);     // função local para definir a cor do tanque

/**
 * Cria um novo jogador.
 * Entrada: número do jogador: 1, 2, ..., MAX_JOGADORES.
 */
Jogador::Jogador(int i): njogador(i)
{
    // define a cor do tanque:
    definir_cor(this->cor, i);
    this->nome = "Jogador " + std::to_string(i);
    this->pontos = 0;
    this->dolares = 0;
    this->homens = 100;
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->normal[0] = 0;
    this->normal[1] = 0;
    this->normal[2] = 1;
    this->angulo = 90;
    this->potencia = 200;
    this->lista_armas = new ListaArmamentos;
}

/**
 * condicao_inicial(): Restaura as configurações do jogador para a condição de
 * início de jogo:
 * - Pontos = 0
 * - Dolares = 0
 * - Armas: Apenas Incinerador, com QTD_INCINERADOR tiros
 */
void Jogador::condicao_inicial()
{
    // zera pontuação e dolares e reseta lista de armamentos
    pontos = 0;
    dolares = 0;
    lista_armas->condicao_inicial();
}

/**
 * Redefine o status do jogador para a condição de início de rodada:
 * - homens = 100
 */
void Jogador::reiniciar()
{
    this->homens = 100;
}


/**
 * Libera a memória utilizada pelo objeto Jogador
 */
Jogador::~Jogador()
{
    // TODO: apagar lista_municoes. Preciso ajudar a função nova_lista_municoes(),
    // que está criando a lista sem fornecer o seu tamanho.
}

/**
 * Desenha o tanque correspondente ao jogador.
 * Utiliza o estado atual do objeto para posicioná-lo. Objeto tanque possuirá
 * atualizados: coordenadas (x, y, z) e o vetor normal do terreno no local onde
 * o tanque se situa.
 *
 * Assume que a matriz ativa é a MODELVIEW.
 * Assume que normal já está normalizado (módulo = 1). É válido, desde que tenha
 * sido obtido a partir da matriz de vetores normais do cenário.
 */
void Jogador::desenhar()
{
    // Calcula o vetor eixo de rotação do tanque
    const double cima[3] = {0, 0, 1};
    double eixo[3] = {0};
    aux::prod_vetorial(cima, normal, eixo);
    double angulo = acos(aux::prod_escalar(cima, normal)) * 180/PI;

    // Translada o tanque para a sua posição no mundo
    glPushMatrix();
    glTranslated(pos[0], pos[1], pos[2]);
    glScaled(TAMANHO_TANQUE, TAMANHO_TANQUE, TAMANHO_TANQUE);

    // Rotaciona o tanque e o desenha
    glPushMatrix();
    glRotated(angulo, eixo[0], eixo[1], eixo[2]);
    desenhar_tanque(cor, homens);
    glPopMatrix();

    // Prepara para desenhar o canhão: translada centro dos eixos para a esfera
    glTranslated(.75/4*normal[0], .75/4*normal[1], .75/4*normal[2]);

    // Gira os eixos para o eixo X do canhão apontar para o ângulo certo
    glRotated(this->angulo, 0, -1, 0);
    desenhar_canhao();

    // Desempilhar a matriz
    glPopMatrix();
}

/**
 * Atalhos para atualizar posição e inclinação do tanque
 */
void Jogador::posicionar(double nova_pos[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->pos[i] = nova_pos[i];
    }
}
void Jogador::definir_normal(GLfloat normal[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->normal[i] = normal[i];
    }
}
/* -------------------------------------------------------------------------- */
/**
 * Função auxiliar que define a cor do tanque de acordo com o número do jogador.
 * A definição da cor segue a mesma sequência que no Tank Wars original.
 * A alteração da cor é realizada por referência.
 */
void definir_cor(float *cor, const int i)
{
    switch (i)
    {
        case 1:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.;
        break;

        case 2:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 3:
        cor[0] = 0.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 4:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 5:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 6:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 7:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 8:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.;
        break;

        case 9:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.5;
        break;

        case 10:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.5;
        break;
    }
}
