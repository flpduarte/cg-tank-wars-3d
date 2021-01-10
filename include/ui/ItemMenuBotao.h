//
// Created by Felipe on 28/01/2019.
//

#ifndef TANKWARS_ITEMMENUBOTAO_H
#define TANKWARS_ITEMMENUBOTAO_H

#include <string>
#include <ui/ItemMenuRetangular.h>

class Mundo;

/**
 * ItemMenuBotao: Implementa a interface ItemMenu.
 *
 * Corresponde à funcionalidade de botão: ao selecioná-lo e apertar enter, ele executará
 * uma ação específica.
 */
class ItemMenuBotao : public ItemMenuRetangular
{
    // ação que o botão executará é salva sob a forma de um ponteiro para uma
    // função a ser executada.
    void (*acao)();
    std::string const rotulo;   // O rótulo do botão
    GLfloat const *cor_rotulo;

public:
    ItemMenuBotao(std::string rotulo, void (acao)(), GLfloat const *cor_rotulo = cor::LILAS);
    ~ItemMenuBotao();

    void desenhar() final;
    void reagir_a_teclado(unsigned char) final;  // Botões reagem à tecla Enter.

private:
    void desenharTextoCentralizadoNoBotao() const;
};


#endif //TANKWARS_ITEMMENUBOTAO_H
