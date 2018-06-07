/**
 * mundo.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa as funções definidas em mundo.hpp
 *
 */

#include "mundo.hpp"
#include "jogador.hpp"
#include "constantes.hpp"

/**
 * Cria o mundo ao iniciar o jogo.
 */
Mundo::Mundo()
{
    // Inicia os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogadores[i] = new Jogador(i + 1);
    }

    // Configurações padrão
    this->tela_atual  = TELA_INICIAL;
    this->n_jogadores = PADRAO_N_JOGADORES;
    this->n_rodadas   = PADRAO_N_RODADAS;

    // Cria o menu principal a partir dos dados do Mundo
    this->configurar_menu_principal();
}

/**
 * Destroi o mundo ao final do jogo
 */
Mundo::~Mundo()
{

    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        delete this->jogadores[i];
    }
}

/**
 * Cria as entradas do menu principal.
 * Entradas são:
 * - Escolha do número de jogadores
 * - Escolha do número de rodadas
 * - Botão "Continuar"
 *
 * Botão continuar deve ser associado à ação "escolher jogadores"
 */
void Mundo::configurar_menu_principal()
{
    // TODO
    return;
}


/**
 * Inicia a tela principal do jogo.
 */
void Mundo::tela_inicial()
{
    this->menu_principal.exibir();
    this->tela_atual = TELA_INICIAL;
}
