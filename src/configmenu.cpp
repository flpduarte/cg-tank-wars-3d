/**
 * configmenu.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções que criam os menus para cada tela do jogo.
 * Elas instanciam as classes implementadas em menu.cpp.
 */
#include "configmenu.hpp"
#include "interacoes.hpp"
#include "interfaces.hpp"
#include "menu.hpp"
#include "mundo.hpp"
#include "jogador.hpp"

/*
Menu *criar_menu_principal();
Menu *criar_menu_renomear_jogadores();
Menu *criar_menu_resultado_parcial();
Menu *criar_menu_compras(int);
*/


/**
 * Cria um menu principal. Retorna o ponteiro para o objeto Menu.
 */
Menu *criar_menu_principal()
{
    Menu *novo = new Menu(200, 600);    // TODO: converter para constantes

    // adiciona opções - TODO
    Botao *iniciar = new Botao("INICIAR", renomear_jogadores);
    novo->inserir_opcao(iniciar);
    return novo;
}