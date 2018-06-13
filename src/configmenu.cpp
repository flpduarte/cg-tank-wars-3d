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

/*
Menu *criar_menu_principal();
Menu *criar_menu_renomear_jogadores();
Menu *criar_menu_resultado_parcial();
Menu *criar_menu_compras(Jogador *);
*/


/**
 * Cria um menu principal. Retorna o ponteiro para o objeto Menu.
 */
Menu *criar_menu_principal()
{
    Menu *novo = new Menu(200, 600);    // TODO: converter para constantes

    // adiciona opções - TODO
    novo->inserir_opcao(new Botao("INICIAR", renomear_jogadores));
    return novo;
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
    Menu *novo = new Menu(200, 600);

    // Insere as opções de renomear cada jogador
    for (unsigned int i = 0; i < mundo.n_jogadores; i++)
    {
        novo->inserir_opcao(new OpcaoEditarNome(mundo.jogadores[i]->nome, MAX_CARACTERES_NOME));
    }

    // Insere botões INICIAR e voltar
    novo->inserir_opcao(new Botao("INICIAR JOGO", iniciar_jogo));
    novo->inserir_opcao(new Botao("Voltar", tela_inicial));
    return novo;
}

Menu *criar_menu_resultado_parcial();

Menu *criar_menu_compras(Jogador *);
