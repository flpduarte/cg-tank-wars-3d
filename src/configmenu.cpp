/**
 * configmenu.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa as funções que criam os menus para cada tela do jogo.
 * Elas instanciam as classes implementadas em menu.cpp.
 */
#include <configmenu.hpp>
#include <mundo.hpp>
#include <globals.hpp>
#include <interacoes.hpp>
#include <jogador.hpp>
#include <ui/ItemMenuEditarNome.h>
#include <iostream>
#include <ui/ItemMenuBotao.h>
#include <ui/ItemMenuAlterarValorNumerico.h>

/**
 * Cria um menu principal. Retorna o ponteiro para o objeto Menu.
 */
Menu *criar_menu_principal()
{
    Menu *menu = new Menu;

    // adiciona opções
    menu->inserir_opcao(new ItemMenuAlterarValorNumerico("Numero de Rodadas", 1, 100, mundo.n_rodadas));
    menu->inserir_opcao(new ItemMenuAlterarValorNumerico("Numero de Jogadores", 2, Mundo::MAX_JOGADORES, mundo.n_jogadores));
    menu->inserir_opcao(new ItemMenuBotao("INICIAR", &renomear_jogadores));
    return menu;
}

/**
 * Cria menu para renomear os jogadores. Será algo do tipo:
 *
 * Jogador 1
 * Jogador 2
 * ...
 * INICIAR JOGO     (botão) -> iniciar_jogo()
 * Voltar           (botão) -> ir_para_tela_inicial()
 */
Menu *criar_menu_renomear_jogadores()
{
    Menu *menu = new Menu();

    // Insere as opções de renomear cada jogador
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        ItemMenuEditarNome *nova = new ItemMenuEditarNome(mundo.jogadores[i]->nome, mundo.jogadores[i]->cor);
        menu->inserir_opcao(nova);
    }

    // Insere botões INICIAR e voltar
    menu->inserir_opcao(new ItemMenuBotao("INICIAR JOGO", iniciar_jogo));
    menu->inserir_opcao(new ItemMenuBotao("Voltar", tela_inicial));
    return menu;
}

/**
 *
 */
Menu *criar_menu_resultado_parcial()
{
    Menu *menu = new Menu;

    // Configura o quadro resultado parcial
    // TODO
    return menu;
}

/**
 * Exibe o menu de compras para o jogador dado.
 * O jogador é passado como argumento para facilitar a escrita da
 * função.
 */
Menu *criar_menu_compras(Jogador *)
{
    // TODO
    return new Menu();
}
