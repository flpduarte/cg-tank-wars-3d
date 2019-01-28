//
// Created by Felipe on 28/01/2019.
//

#ifndef TANKWARS_BOTAO_H
#define TANKWARS_BOTAO_H

#include <string>
#include "ItemMenu.h"

/**
 * Botao: Implementa a interface ItemMenu.
 *
 * Corresponde à funcionalidade de botão: ao selecioná-lo e apertar enter, ele executará
 * uma ação específica.
 */
class Botao : public ItemMenu
{
    // ação que o botão executará é salva sob a forma de um ponteiro para uma
    // função a ser executada.
    void (*acao)(void);

public:
    void desenhar();
    void reagir_a_teclado(unsigned char);  // Botões reagem à tecla Enter.

    Botao(std::string, void (void));
    ~Botao();
};


#endif //TANKWARS_BOTAO_H
