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
    cor::definir_cor(this->cor_alterada, this->cor);
    this->nome = "Jogador " + std::to_string(i);
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->normal[0] = 0;
    this->normal[1] = 0;
    this->normal[2] = 1;
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
    this->pontos = 0;
    this->dolares = 0;
    this->lista_armas->condicao_inicial();
}

/**
 * Redefine o status do jogador para a condição de início de rodada:
 * - homens = 100
 * - vivo   = true
 */
void Jogador::reiniciar()
{
    this->homens   = 100;
    this->vivo     = true;
    this->angulo   = 90;
    this->potencia = 200;
}


/**
 * Retorna o ângulo do tanque em formato de string, para ser exibido na tela.
 * Formato:
 * [0, 90]: "45 >"      Sinal de maior indica a direção - direita
 *
 * (90, 180]: "45 <"    Sinal de menor indica a direção - esquerda
 */
std::string Jogador::angulo_texto()
{
    return angulo > 90 ? std::to_string(angulo - 90) + " <" : std::to_string(angulo) + " >";
}


/**
 * Libera a memória utilizada pelo objeto Jogador
 */
Jogador::~Jogador()
{
    delete lista_armas;
}


/**
 * Retorna a cor "real" do tanque - homens/100 * cor.
 */
float *Jogador::cor_real()
{
    // altera só as componentes RGB. Componente A permanece = 1.
    for (int i = 0; i < 3; i++)
    {
        cor_alterada[i] = cor[i]*homens/100.;
    }
    return cor_alterada;
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
    desenhar_tanque(this->cor_real());
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


/**
 * atirar()
 * Lança um projétil a partir do tanque atual.
 * O projétil é criado na ponta do canhão do tanque, com velocidade inicial
 * dada pela multiplicação da potência pelo fator constante POT_PARA_VEL.
 *
 * Entrada: velocidade do vento, recebido do cenário.
 */
void atirar(int vento)
{
    // TODO;
}

/**
 * explodir(): realiza a animação de explosão do tanque.
 */
void explodir()
{
    // TODO
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
