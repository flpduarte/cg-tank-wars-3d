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
#include <iostream>
#include "menu.hpp"
#include "constantes.hpp"
#include "objetos2D.hpp"
#include "interacoes.hpp"

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
Botao::Botao(std::string tit, void fn()) :
    OpcaoMenu(tit), acao(fn)
{
    cor::definir_cor(cor_titulo, cor::LILAS);
}
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
        glColor4fv(cor::CINZA_ESCURO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor4fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // desenha borda
    desenhar_borda(largura, altura, this->cor_borda);

    // Imprime texto no centro do botão
    glPushMatrix();
    glTranslatef(largura/2, altura/2, 0);
    texto_centralizado(this->titulo, 0.8*altura, FONTE, this->cor_titulo);
    glPopMatrix();
}

/**
 * reagir_a_teclado(tecla)
 * Quando o botão está selecionado e enter for pressionado, executa a função
 * gravada em this->acao.
 */
void Botao::reagir_a_teclado(unsigned char tecla)
{
    if ((tecla == '\n' || tecla == '\r') && this->selecionado)
    {
        this->acao();
    }
}

/* --- Métodos de OpcaoAlterarValorNumerico --- */
/**
 * Construtor e destrutor
 */
OpcaoAlterarValorNumerico::OpcaoAlterarValorNumerico(std::string tit, int mn, int mx, int &ref):
    OpcaoMenu(tit), min(mn), max(mx), referencia(ref)
{
    cor::definir_cor(cor_referencia, cor::VERDE);
}

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
        glColor4fv(cor::CINZA_ESCURO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor4fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // desenha borda
    desenhar_borda(this->largura, this->altura, this->cor_borda);

    // Escrever texto
    std::string texto = this->titulo + ": - " + std::to_string(referencia) + " +";
    glPushMatrix();
    glTranslatef(largura/2, altura/2, 0);
    texto_centralizado(texto, 0.8*altura, FONTE, this->cor_referencia);
    glPopMatrix();

}

/* --- Funções da classe OpcaoEditarNome --- */
/**
 * Construtor e destrutor
 */
OpcaoEditarNome::OpcaoEditarNome(std::string &nome, unsigned int max):
    OpcaoMenu(nome),  max_caracteres(max), referencia(nome) {}
OpcaoEditarNome::~OpcaoEditarNome() {}

/**
 * Reagir a teclado: para permitir edição do nome
 */
void OpcaoEditarNome::reagir_a_teclado(unsigned char tecla)
{
    // Se não estiver no modo edição, reage apenas a enter.
    if (bloqueia_cursor == false)
    {
        if ((tecla == '\n') || (tecla == '\r'))
        {
            bloqueia_cursor = true;
        }
    }

    // Quando modo edição estiver ativo, permitir digitar!
    else
    {
        // Enter: desativa modo edição e salva string na referência
        if ((tecla == '\n') || (tecla == '\r'))
        {
            bloqueia_cursor = false;
            referencia = titulo;
        }

        // Backspace: apaga o último caractere - enquanto existirem caracteres
        else if ((tecla == '\b') && (titulo.size() > 0))
        {
            titulo.erase(titulo.end() - 1);
        }

        // Teclas alfanuméricas e espaço: Acrescenta ao string
        else if ((isalnum(tecla) || tecla == ' ') && titulo.size() < max_caracteres)
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
    // desenha fundo do quadro como cinza se selecionado
    if (this->selecionado)
    {
        glColor4fv(cor::CINZA_ESCURO);
    }

    // desenha na cor original, caso contrário
    else
    {
        glColor4fv(this->cor_fundo);
    }
    glRectf(0, 0, this->largura, this->altura);

    // desenha borda
    glColor4fv(this->cor_borda);
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(largura, 0, 0);
        glVertex3f(largura, altura, 0);
        glVertex3f(0, altura, 0);
    glEnd();

    // Imprime texto alinhado à esquerda
    glPushMatrix();
    glTranslatef(10, altura/2, 0);
    desenhar_string(bloqueia_cursor ? this->titulo + "|" : this->titulo, 4*altura/5., FONTE, this->cor_titulo);
    glPopMatrix();
}
