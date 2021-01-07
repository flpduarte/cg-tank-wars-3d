//
// Created by Felipe on 10/01/2019.
//

#ifndef TANKWARS_ITEMMENU_H
#define TANKWARS_ITEMMENU_H

#include <string>
#include <constantes.hpp>
#include <GL/gl.h>

using namespace std;

/**
 * Classe abstrata ItemMenu.
 * Representa um item do menu.
 */
class ItemMenu {

// inclui borda

public:

    //std::string titulo;
    bool selecionavel;      // Indica se o quadro é selecionavel ou não.
    bool selecionado;       // Indica se o cursor encontra-se nesta posição.
    bool bloqueia_cursor;   // Quando true, o cursor não muda de item menu quando as teclas direcionais são apertadas.


public:
    ItemMenu();
    virtual ~ItemMenu() = 0;            // Obriga classes filhas a definirem um destrutor. TODO: analisar a necessidade dessa obrigação

    // getters altura e largura do retângulo que cerca o formato do item menu (não necessariamente é retangular.)
    virtual GLfloat getAltura() = 0;
    virtual GLfloat getLargura() = 0;

    // Desenha o item na tela, incluindo suas cores.
    virtual void desenhar() = 0;

    // Como o item menu reage a teclas especiais (setas, etc.). Comportamento padrão: sem reação.
    virtual void reagir_a_tecla_especial(int tecla);

    // Como o item menu reage às demais teclas. Padrão: sem reação.
    virtual void reagir_a_teclado(unsigned char);


};

#endif //TANKWARS_ITEMMENU_H
