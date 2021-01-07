//
// Created by Felipe on 30/12/2020.
//

#include <ui/ItemMenuEditarNome.h>


ItemMenuRetangular::ItemMenuRetangular(unsigned int largura, unsigned int altura, GLfloat const *cor_borda,
                                       GLfloat const *cor_fundo) :
        largura(largura), altura(altura), cor_borda(cor_borda), cor_fundo(cor_fundo) {}

/**
 * Desenha a borda e o fundo de um item menu retangular.
 * Deve ser utilizado pelas subclasses de ItemMenuRetangular.
 */
void ItemMenuRetangular::desenharRetangulo() const {// desenha fundo do quadro como cinza se selecionado
    if (selecionado)
    {
        glColor4fv(cor::CINZA_ESCURO);
    }
    else
    {
        glColor4fv(cor_fundo);
    }
    glRectf(0, 0, largura, altura);

    // desenha borda
    glColor4fv(cor_borda);
    glLineWidth(ITEM_MENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(largura, 0, 0);
    glVertex3f(largura, altura, 0);
    glVertex3f(0, altura, 0);
    glEnd();
}

GLfloat ItemMenuRetangular::getAltura() {
    return altura;
}

GLfloat ItemMenuRetangular::getLargura() {
    return largura;
}
