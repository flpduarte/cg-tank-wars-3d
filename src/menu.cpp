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

        glColor3fv(cor::CINZA_MEDIO);
    }
    // desenha na cor original, caso contrário
    else
    {
        glColor3fv(this->cor_fundo);
    }
    glRecti(0, 0, this->largura, this->altura);

    // desenha borda
    glLineWidth(OPCAOMENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
        glVertex3i(0, 0, 0);
        glVertex3i(largura, 0, 0);
        glVertex3i(largura, altura, 0);
        glVertex3i(0, altura, 0);
    glEnd();

    // TODO:
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
