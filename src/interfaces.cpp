/**
 * interfaces.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa os métodos não abstratos das interfaces.
 */
#include <cmath>
#include <GL/glut.h>
#include "interfaces.hpp"
#include "constantes.hpp"

/* --- Implementação do construtor de OpcaoMenu --- */
/**
 * Cria um objeto OpcaoMenu com largura e altura padrões.
 */
OpcaoMenu::OpcaoMenu(std::string tit):
    largura(OPCAOMENU_LARGURA_PADRAO),
    altura(OPCAOMENU_ALTURA_PADRAO),
    titulo(tit),
    selecionado(false)
{
    // define cores padrão
    cor::definir_cor(cor_borda, cor::BRANCO);
    cor::definir_cor(cor_fundo, cor::PRETO);
    cor::definir_cor(cor_titulo, cor::BRANCO);
}


/* --- Implementação das funções da classe Menu --- */
/**
 * Inicia objeto Menu
 */
Menu::Menu(int x0, int y0): posx0(x0), posy0(y0), opcao_ativa(0) {}

/**
 * Insere uma opção de menu.
 */
void Menu::inserir_opcao(OpcaoMenu *opcao)
{
    this->opcoes.push_back(opcao);
}

/**
 * Teclas especiais:
 * - Setas para cima e para baixo mudam a opção ativa.
 * - Setas para a esquerda/direita são passadas para a própria opção, questions
 *   decidirá como reagir dependendo da sua implementação.
 */
void Menu::gerenciar_teclas_especiais(int tecla)
{
    switch (tecla)
    {
        case GLUT_KEY_UP:
            if (this->opcao_ativa > 0)
            {
                this->opcoes[this->opcao_ativa--]->selecionado = false; // usa valor, depois decrementa
                this->opcoes[this->opcao_ativa]  ->selecionado = true;
            }
            break;

        case GLUT_KEY_DOWN:
            if (this->opcao_ativa < this->opcoes.size() - 1)
            {
                this->opcoes[this->opcao_ativa++]->selecionado = false;
                this->opcoes[this->opcao_ativa]  ->selecionado = true;
            }
            break;

        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            this->opcoes[this->opcao_ativa]->reagir_a_tecla_especial(tecla);
            break;

    }
    // Reexibe informações na tela após atualizar o menu
    glutPostRedisplay();
}

/**
 * Teclas comuns do teclado - inclusive enter
 * Transfere ação para a opção ativa.
 */
void Menu::gerenciar_teclado(unsigned char tecla)
{
    this->opcoes[this->opcao_ativa]->reagir_a_teclado(tecla);
    glutPostRedisplay();
}


/**
 * Desenha o menu na tela. Posiciona cada menu em sua respectiva posição.
 * Parte do pressuposto de que o mundo é 2D (podemos mudar isso no futuro).
 */
void Menu::exibir()
{
    // confirma matriz atual é a model-view.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Desenha cada objeto OpcaoMenu e o posiciona no mundo.
    // Translada ao início do menu
    glTranslatef(this->posx0, this->posy0, 0);
    for (unsigned int i = 0; i < this->opcoes.size(); i++)
    {
        // translada para baixo, pois a origem de cada caixa é em seu canto
        // inferior esquerdo.
        glTranslatef(0, -this->opcoes[i]->altura, 0);   // translações somam-se propositalmente
        this->opcoes[i]->desenhar();
    }

    // Retorna à matriz identidade
    glPopMatrix();
}

/* --- Implementação das funções da classe Municao --- */
/**
 * Valor da derivada do i-ésima variável de estado,
 * no instante atual. O tempo foi desprezado porque
 * não há nenhuma grandeza que dependa do tempo.
 */
double Municao::derivada(int i)
{
    // Derivada da posição = velocidade
    if (i < 3)
    {
        return X[i + 3];
    }

    // Derivada da velocidade = aceleração.
    // Aceleração = Força / Massa.
    // Esta função calcula a aceleração componente por componente.
    else
    {
        return F[i - 3]/massa;
    }
}

/**
 * atualizar_posicao()
 * Usa o método de integração de Euler para atualizar as variáveis de estado
 */
void Municao::atualizar_posicao()
{
    for (int i = 0; i < 6; i++)
    {
        X[i] += derivada(i) * DT;
    }
}


/**
 * lancar(X0, V0, angulo, vento)
 * Define as coordenadas iniciais do projétil na tela ao ser lançado.
 */
void Municao::lancar(int X0[3], int V0, int ang, int vento)
{
    // Posição
    X[0] = X0[0];
    X[1] = X0[1];
    X[2] = X0[2];

    // Velocidade
    X[3] = V0*cos(ang);     // Vx
    X[4] = 0;               // Vy
    X[5] = V0*sin(ang);     // Vz

    // Forças
    F[0] =  massa*vento;        // Efeito do vento
    F[1] =  0.;
    F[2] = -massa*GRAVIDADE;    // Efeito da gravidade
}