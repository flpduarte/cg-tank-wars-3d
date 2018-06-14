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
#include "globals.hpp"
#include "interacoes.hpp"
#include "menu.hpp"
#include "mundo.hpp"
#include "jogador.hpp"

/**
 * Cria um menu principal. Retorna o ponteiro para o objeto Menu.
 */
Menu *criar_menu_principal()
{
    //Menu *menu = new Menu(300, 300);    // TODO: converter para constantes
    Menu *menu = new Menu;

    // adiciona opções - TODO
    menu->inserir_opcao(new OpcaoAlterarValorNumerico("Numero de Jogadores", 2, MAX_JOGADORES, mundo.n_jogadores));
    menu->inserir_opcao(new Botao("INICIAR", renomear_jogadores));
    return menu;
}

/**
 * Cria menu para renomear os jogadores. Será algo do tipo:
 *
 * Jogador 1        (título editável: implementar)
 * Jogador 2        (título editável: implementar)
 * ...
 * INICIAR JOGO     (botão) -> iniciar_jogo()
 * Voltar           (botão) -> tela_inicial()
 */
Menu *criar_menu_renomear_jogadores()
{
    // TODO: ajustar posição
    //Menu *menu = new Menu(200, 600);
    Menu *menu = new Menu();

    // Insere as opções de renomear cada jogador
    for (unsigned int i = 0; i < mundo.n_jogadores; i++)
    {
        menu->inserir_opcao(new OpcaoEditarNome(mundo.jogadores[i]->nome, MAX_CARACTERES_NOME));
    }

    // Insere botões INICIAR e voltar
    menu->inserir_opcao(new Botao("INICIAR JOGO", iniciar_jogo));
    menu->inserir_opcao(new Botao("Voltar", tela_inicial));
    return menu;
}

/**
 *
 */
Menu *criar_menu_resultado_parcial()
{
    //Menu *menu = new Menu(200, 600);
    Menu *menu = new Menu;

    // Configura o quadro resultado parcial


    return menu;
}

/**
 * Exibe o menu de compras para o jogador dado.
 * O jogador é passado como argumento para facilitar a escrita da
 * função.
 */
Menu *criar_menu_compras(Jogador *)
{
    //Menu *menu = new Menu(200, 600);
    //return menu;
    return new Menu();
}
