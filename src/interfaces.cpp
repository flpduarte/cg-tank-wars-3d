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
#include <iostream>
#include "interfaces.hpp"
#include "constantes.hpp"
#include "auxiliares.hpp"

/* --- Implementação do construtor de OpcaoMenu --- */
/**
 * Cria um objeto OpcaoMenu com largura e altura padrões.
 */
OpcaoMenu::OpcaoMenu(std::string tit):
    largura(OPCAOMENU_LARGURA_PADRAO),
    altura(OPCAOMENU_ALTURA_PADRAO),
    titulo(tit),
    selecionavel(true),
    selecionado(false),
    bloqueia_cursor(false)
{
    // define cores padrão
    cor::definir_cor(cor_borda, cor::BRANCO);
    cor::definir_cor(cor_fundo, cor::PRETO);
    cor::definir_cor(cor_titulo, cor::BRANCO);
}

/* É estranho, mas é preciso definir o destrutor */
OpcaoMenu::~OpcaoMenu() {}

/* Reações padrão às funções reagir_a_tecla_especial() e reagir_a_teclado() */
void OpcaoMenu::reagir_a_teclado(unsigned char tecla) {}
void OpcaoMenu::reagir_a_tecla_especial(int tecla) {}


/* --- Implementação das funções da classe Menu --- */
/**
 * Inicia objeto Menu
 */
//Menu::Menu(int x0, int y0):
Menu::Menu():
    largura(0),
    altura(0),
    posx0(0),
    posy0(0),
    opcao_ativa(0),
    _possui_opcao_selecionada(false),
    posicionamento_automatico(true) {}

/**
 * Insere uma opção de menu.
 */
void Menu::inserir_opcao(OpcaoMenu *opcao)
{
    // Ao inserir opções, muda a propriedade selecionado para
    // true ao encontrar a primeira opção "selecionável" -
    // uma que o cursor possa selecionar.
    this->opcoes.push_back(opcao);
    if (!_possui_opcao_selecionada)
    {
        if ((this->opcao_ativa == (this->opcoes.size() - 1)) && opcao->selecionavel)
        {
            opcao->selecionado = true;
            _possui_opcao_selecionada = true;   // não precisa mais fazer esta verificação
        }

        // Se a opção inserida não for selecionável, tenta o próximo
        else
        {
            this->opcao_ativa++;
        }
    }

    // Recalcula as dimensões do menu e a sua origem
    this->altura += opcao->altura;
    if (opcao->largura > this->largura)
        this->largura = opcao->largura;

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
    OpcaoMenu *opcao_atual = this->opcoes[this->opcao_ativa];
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
    for (unsigned int i = 0; i < this->opcoes.size(); i++)
    {
        delete this->opcoes[i];
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

    // Desenha cada objeto OpcaoMenu e o posiciona no mundo.
    // Translada ao início do menu
    glTranslatef(this->posx0, this->posy0, 0);
    for (unsigned int i = 0; i < this->opcoes.size(); i++)
    {
        // translada para baixo, pois a origem de cada caixa é em seu canto
        // inferior esquerdo.
        glTranslatef(0, -(float)this->opcoes[i]->altura, 0);   // CUIDADO: converter unsigned int para float!
        this->opcoes[i]->desenhar();
    }

    // Retorna à matriz identidade
    glPopMatrix();
}

/* --- Implementação das funções da classe Municao --- */

/**
 * lancar(X0, V0, angulo, vento)
 * Cria um objeto Projetil com as características dadas.
 */
Projetil *Municao::lancar(double X0[3], int V0, int ang, int vento)
{
    return new Projetil(this, X0, V0, ang, vento);
}

double Municao::massa()
{
    return m;
}

/* --- Implementação das funções da classe Projetil --- */
/**
 * Cria um novo projétil no local designado.
 */
Projetil::Projetil(Municao *m, double X0[3], int V0, int ang, int vento)
{
    municao = m;

    // Posição
    X[0] = X0[0];
    X[1] = X0[1];
    X[2] = X0[2];

    // Velocidade
    X[3] = V0*cos(ang);     // Vx
    X[4] = 0;               // Vy
    X[5] = V0*sin(ang);     // Vz

    // Forças
    F[0] =  m->massa()*vento;        // Efeito do vento
    F[1] =  0.;
    F[2] = -m->massa()*GRAVIDADE;    // Efeito da gravidade
}

/**
 * Valor da derivada do i-ésima variável de estado,
 * no instante atual. O tempo foi desprezado porque
 * não há nenhuma grandeza que dependa do tempo.
 */
double Projetil::derivada(int i)
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
        return F[i - 3]/municao->massa();
    }
}


/**
 * atualizar_posicao()
 * Usa o método de integração de Euler para atualizar as variáveis de estado
 */
void Projetil::atualizar_posicao()
{
    for (int i = 0; i < 6; i++)
    {
        X[i] += derivada(i) * DT;
    }
}

/**
 * Desenha o projétil conforme modelo definido pela munição.
 * Translada o desenho para a localização do projétil.
 */
void Projetil::desenhar()
{
    // Transladar o projétil e alinhá-lo com o vetor velocidade.
    // Primeiro normalizar o vetor velocidade
    const double V = sqrt(X[3]*X[3] + X[4]*X[4] + X[5]*X[5]);
    const double vetorV[3] = {X[3]/V, X[4]/V, X[5]/V};

    // Agora encontrar o ângulo entre o eixo X do projétil (longitudinal) e o
    // vetor velocidade
    const double frente[3] = {1, 0, 0};
    double eixo[3] = {0};
    aux::prod_vetorial(frente, vetorV, eixo);
    double angulo = acos(aux::prod_escalar(frente, vetorV)) * 180/PI;

    // Desenha o projétil
    glPushMatrix();
    glTranslated(X[0], X[1], X[2]);
    glRotated(angulo, eixo[0], eixo[1], eixo[2]);
    municao->desenhar();
    glPopMatrix();
}
