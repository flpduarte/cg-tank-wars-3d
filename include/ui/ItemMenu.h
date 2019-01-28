//
// Created by Felipe on 10/01/2019.
//

#ifndef TANKWARS_ITEMMENU_H
#define TANKWARS_ITEMMENU_H

#include <constantes.hpp>

using namespace std;

/**
 * Classe abstrata ItemMenu.
 * Representa um item do menu.
 */
class ItemMenu {

protected:
    /* Dimensões padrão das opções de menu */
    static const int ITEM_MENU_LARGURA_PADRAO = 600;
    static const int ITEM_MENU_ALTURA_PADRAO  = 50;                                         // inclui borda
    static const int ITEM_MENU_POSX_PADRAO    = 0;
    static const int ITEM_MENU_POSY_PADRAO    = JANELA_ALTURA - ITEM_MENU_ALTURA_PADRAO;
    static const int ITEM_MENU_LARGURA_BORDA  = 4;

    // propriedades a serem herdadas
public:
    unsigned int largura;
    unsigned int altura;
    std::string titulo;
    bool selecionavel;      // Indica se o quadro é selecionavel ou não.
    bool selecionado;       // Indica se o cursor encontra-se nesta posição.
    bool bloqueia_cursor;   // Um estado que indica se ele impede a mudança para
                            // outras opções por meio das setas para cima e para baixo

    // cores em RGBA
    float cor_borda[4];
    float cor_fundo[4];
    float cor_titulo[4];

    ItemMenu(std::string titulo);                          // Cria objeto com altura e largura padrão. Pode ser modificado depois.
    virtual ~ItemMenu() = 0;                               // Obriga classes filhas a definirem um destrutor. TODO: analisar a necessidade dessa obrigação

    virtual void desenhar() = 0;                            // Virtual puro, classes filhas DEVEM implementá-lo.
    virtual void reagir_a_tecla_especial(int tecla);        // se não implementado, esta opção não reage a teclas especiais.
    virtual void reagir_a_teclado(unsigned char);           // retorna true se precisar atualizar a tela após a ação.

    void desenhar_borda(const unsigned int largura, const unsigned int altura, const float cor[4]);
};


#endif //TANKWARS_ITEMMENU_H
