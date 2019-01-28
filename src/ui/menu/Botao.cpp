//
// Created by Felipe on 28/01/2019.
//

#include <ui/Botao.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <objetos2D.hpp>

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
        ItemMenu(tit), acao(fn)
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
