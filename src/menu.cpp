/**
 * menu.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Contém a implementação das classes que implementam a interface OpcaoMenu.
 */
#include <GL/glut.h>
#include "menu.hpp"
#include "constantes.hpp"

/* --- Classe Botao --- */
/**
 * Inicia a classe Botão. Recebe como entrada uma função a ser chamada quando o
 * botão é apertado.
 *
 * Entradas:
 * - tit: título do botão
 * - fn : Ação a executar quando o botão é selecionado e Enter é pressionado.
 *
 * ~Botao(): função destrutora da classe botão; nada a fazer.
 */
Botao::Botao(std::string tit, void fn()) : OpcaoMenu(tit), acao(fn) {}
Botao::~Botao() {}

/**
 * desenhar()
 * Desenha o botão na tela!
 */
void Botao::desenhar()
{
    // desenha fundo do quadro como cinza se selecionado
    if (this->selecionado)
    {
        glColor3fv(cor::CINZA_ESCURO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor3fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // desenha borda
    glColor3fv(this->cor_borda);
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(largura, 0, 0);
        glVertex3f(largura, altura, 0);
        glVertex3f(0, altura, 0);
    glEnd();

    // TODO: escrever texto dentro da caixa
    return;
}

/**
 * reagir_a_teclado(tecla)
 * Quando o botão está selecionado e enter for pressionado, executa a função
 * gravada em this->acao.
 */
void Botao::reagir_a_teclado(unsigned char tecla)
{
    if (tecla == '\n' && this->selecionado)
    {
        this->acao();
    }
}

/* --- Métodos de OpcaoAlterarValorNumerico --- */
/**
 * Construtor e destrutor
 */
OpcaoAlterarValorNumerico::OpcaoAlterarValorNumerico(std::string tit, unsigned int mn, unsigned int mx, unsigned int &ref):
    OpcaoMenu(tit), min(mn), max(mx), referencia(ref) {}

OpcaoAlterarValorNumerico::~OpcaoAlterarValorNumerico() {}

/**
 * Reação a teclas especiais: reage à seta esquerda ou direita.
 * Esquerda: diminui o valor
 * Direita : aumenta o valor
 */
void OpcaoAlterarValorNumerico::reagir_a_tecla_especial(int tecla)
{
    switch (tecla)
    {
        case (GLUT_KEY_LEFT):
            if (this->referencia > this->min)
                this->referencia--;
            break;

        case (GLUT_KEY_RIGHT):
            if (this->referencia < this->max)
                this->referencia++;
            break;
    }
}

/**
 * Desenha o quadro
 */
void OpcaoAlterarValorNumerico::desenhar()
{
    // desenha fundo do quadro como cinza se selecionado
    if (this->selecionado)
    {
        glColor3fv(cor::CINZA_MEDIO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor3fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // desenha borda
    glColor3fv(this->cor_borda);
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(largura, 0, 0);
        glVertex3f(largura, altura, 0);
        glVertex3f(0, altura, 0);
    glEnd();

    // TODO: escrever texto dentro da caixa
    return;
}

/* --- Funções da classe OpcaoEditarNome --- */
/**
 * Construtor e destrutor
 */
OpcaoEditarNome::OpcaoEditarNome(std::string &nome, unsigned int max):
    OpcaoMenu(nome),  max_caracteres(max), referencia(nome), modo_edicao(false) {}
OpcaoEditarNome::~OpcaoEditarNome() {}

/**
 * Reagir a teclado: para permitir edição do nome
 */
void OpcaoEditarNome::reagir_a_teclado(unsigned char tecla)
{
    // Se não estiver no modo edição, reage apenas a enter
    if (modo_edicao == false)
    {
        if ((tecla == '\n') || (tecla == '\r'))
        {
            modo_edicao = true;
        }
    }

    // Quando modo edição estiver ativo, permitir digitar!
    else
    {
        // Enter: desativa modo edição e salva string na referência
        if ((tecla == '\n') || (tecla == '\r'))
        {
            modo_edicao = false;
            referencia = titulo;
        }

        // Backspace: apaga o último caractere
        else if (tecla == '\b')
        {
            titulo.erase(titulo.end() - 1);
        }

        // Teclas alfanuméricas e espaço: Acrescenta ao string
        else if (isalnum(tecla) || tecla == ' ')
        {
            titulo += tecla;
        }

        // Ignora todas as outras teclas
    }
}

/**
 * Desenha o quadro da opção de editar nome!
 */
void OpcaoEditarNome::desenhar()
{
    // desenha borda
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(largura, 0, 0);
        glVertex3f(largura, altura, 0);
        glVertex3f(0, altura, 0);
    glEnd();

    // desenha fundo do quadro como cinza se selecionado
    if (this->selecionado)
    {
        glColor3fv(cor::CINZA_MEDIO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor3fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // TODO: escrever texto dentro da caixa
    std::string texto = this->titulo + "|"; // acrescenta um cursor
    return;
}
