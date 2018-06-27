/**
 * configmenu.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Contém as funções que criam os menus para cada tela do jogo.
 * Elas instanciam as classes implementadas em menu.cpp.
 */
#ifndef CONFIGMENU_HPP
#define CONFIGMENU_HPP

#include "menu.hpp"
#include "jogador.hpp"

Menu *criar_menu_principal();
Menu *criar_menu_renomear_jogadores();
Menu *criar_menu_resultado_parcial();
Menu *criar_menu_compras(Jogador *);

#endif
