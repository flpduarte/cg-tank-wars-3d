/**
 * menu.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa a classe Menu.
 */
#include <ui/Menu.hpp>
#include <GL/glut.h>

//Menu::Menu(int x0, int y0):
Menu::Menu():
        largura(0),
        altura(0),
        posx0(0),
        posy0(0),
        opcao_ativa(0),
        possui_opcao_selecionada(false),
        posicionamento_automatico(true) {}

/**
 * Insere uma opção de menu.
 */
void Menu::inserir_opcao(ItemMenu *opcao)
{
    // Ao inserir opções, muda a propriedade selecionado para
    // true ao encontrar a primeira opção "selecionável" -
    // uma que o cursor possa selecionar.
    this->opcoes.push_back(opcao);
    if (!possui_opcao_selecionada)
    {
        if ((this->opcao_ativa == (this->opcoes.size() - 1)) && opcao->selecionavel)
        {
            opcao->selecionado = true;
            possui_opcao_selecionada = true;   // não precisa mais fazer esta verificação
        }

        // Se a opção inserida não for selecionável, tenta o próximo
        else
        {
            this->opcao_ativa++;
        }
    }

    // Recalcula as dimensões do menu e a sua origem
    this->altura += opcao->getAltura();
    if (opcao->getLargura() > this->largura)
        this->largura = opcao->getLargura();

    if (this->posicionamento_automatico)
        this->recalcular_origem();
}

/**
 * Recalcula a origem do menu de forma que ele seja exibido no centro da tela.
 * É chamada a cada inserção de linhas ao menu, desde que posicionamento_automatico
 * = true.
 */
void Menu::recalcular_origem()
{
    this->posx0 = (glutGet(GLUT_WINDOW_WIDTH) - this->largura)/2;
    this->posy0 = (glutGet(GLUT_WINDOW_HEIGHT) + this->altura)/2;
}

/**
 * Teclas especiais:
 * - Setas para cima e para baixo mudam a opção ativa.
 * - Setas para a esquerda/direita são passadas para a própria opção, questions
 *   decidirá como reagir dependendo da sua implementação.
 */
void Menu::gerenciar_teclas_especiais(int tecla)
{
    ItemMenu *opcao_atual = this->opcoes[this->opcao_ativa];
    switch (tecla)
    {
        // Menu reage às teclas para cima e para baixo - desde que a opção ativa não bloqueou o cursor
        case GLUT_KEY_UP:
            if (!(opcao_atual->bloqueia_cursor) && (this->opcao_ativa > 0))
            {
                this->opcoes[this->opcao_ativa--]->selecionado = false;
                this->opcoes[this->opcao_ativa]  ->selecionado = true;
            }
            break;

        case GLUT_KEY_DOWN:
            if (!(opcao_atual->bloqueia_cursor) && (this->opcao_ativa < this->opcoes.size() - 1))
            {
                this->opcoes[this->opcao_ativa++]->selecionado = false;
                this->opcoes[this->opcao_ativa]  ->selecionado = true;
            }
            break;

        // Todos os outros casos: deixa a cargo da opção ativa
        default:
            opcao_atual->reagir_a_tecla_especial(tecla);
            break;

    }
    // Reexibe informações na tela após atualizar o menu
    glutPostRedisplay();
}

/**
 * Libera a memória usada pelas opções do Menu antes de destruí-lo.
 */
Menu::~Menu()
{
    for (auto & opcao : this->opcoes)
    {
        delete opcao;
    }
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

    // Desenha cada objeto ItemMenu e o posiciona no mundo.
    // Translada ao início do menu
    glTranslatef(this->posx0, this->posy0, 0);
    for (auto & opcao : this->opcoes)
    {
        // translada para baixo, pois a origem de cada caixa é em seu canto
        // inferior esquerdo.
        glTranslatef(0, -(float)opcao->getAltura(), 0);   // CUIDADO: converter unsigned int para float!
        opcao->desenhar();
    }

    // Retorna à matriz identidade
    glPopMatrix();
}