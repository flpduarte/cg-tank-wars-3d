//
// Created by Felipe on 30/12/2020.
//

#ifndef TANKWARS_ITEMMENURETANGULAR_H
#define TANKWARS_ITEMMENURETANGULAR_H


#include <ui/ItemMenu.h>
#include <string>
#include <constantes.hpp>
#include <GL/gl.h>
#include <graphics/cor.h>
#include <ui/ItemMenuRetangular.h>

class ItemMenuRetangular : public ItemMenu {

protected:
    unsigned int const largura;
    unsigned int const altura;
    GLfloat const *cor_fundo;
    GLfloat const *cor_borda;

    /* Dimensões padrão das opções de menu */
    static const int ITEM_MENU_LARGURA_PADRAO = 600;
    static const int ITEM_MENU_ALTURA_PADRAO  = 50;
    static const int ITEM_MENU_POSX_PADRAO    = 0;
    static const int ITEM_MENU_POSY_PADRAO    = JANELA_ALTURA - ITEM_MENU_ALTURA_PADRAO;
    static const int ITEM_MENU_LARGURA_BORDA  = 4;

public:
    ItemMenuRetangular(unsigned int largura = ITEM_MENU_LARGURA_PADRAO, unsigned int altura = ITEM_MENU_ALTURA_PADRAO,
                       GLfloat const *cor_borda = cor::BRANCO, GLfloat const *cor_fundo = cor::PRETO);

    GLfloat getAltura() override;

    GLfloat getLargura() override;

protected:
    void desenharRetangulo() const;
};


#endif //TANKWARS_ITEMMENURETANGULAR_H
