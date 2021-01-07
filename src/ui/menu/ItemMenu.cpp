//
// Created by Felipe on 10/01/2019.
//

#include <ui/ItemMenu.h>

using namespace std;

/* --- Implementação do construtor de ItemMenu --- */
/**
 * Cria um objeto OpcaoMenu com largura e altura padrões.
 */
ItemMenu::ItemMenu():
        selecionavel(true),
        selecionado(false),
        bloqueia_cursor(false)
{}

/* É estranho, mas é preciso definir o destrutor */
ItemMenu::~ItemMenu() = default;

/* Reações padrão às funções reagir_a_tecla_especial() e reagir_a_teclado(): sem reação. */
void ItemMenu::reagir_a_teclado(unsigned char tecla) {}
void ItemMenu::reagir_a_tecla_especial(int tecla) {}



