/**
 * mundo.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Define a classe Mundo e outros dados associados.
 *
 */
#ifndef MUNDO_HPP
#define MUNDO_HPP

#include "cenario.hpp"
#include "constantes.hpp"
#include "jogador.hpp"
#include "interfaces.hpp"

/**
 * Mundo: Contém as variáveis de estado do mundo tais como tela atual, no. de
 * jogadores, etc.
 */
class Mundo
{
public:
    // Lista de jogadores. Só estarão ativos os jogadores de 0 a n_jogadores - 1
    Jogador *jogadores[MAX_JOGADORES];

    // configurações do jogo
    int n_jogadores;    // 2, ..., MAX_JOGADORES <= 10
    int n_rodadas;      // > 0

    // estado atual do mundo
    Tela tela_atual;
    int rodada_atual;   // 1, 2, ..., n_rodadas

    // Construtor e destrutor
    Mundo();
    ~Mundo();

    // Métodos que transicionam de uma tela para outra e realizam o loop do jogo
    void tela_inicial();            // Vai para a tela inicial
    void renomear_jogadores();      // Tela inicial -> Escolha jogadores
    void iniciar_jogo();            // Escolha jogadores -> jogo
    void iniciar_rodada();          // Inicia o loop de uma rodada_atual
    void resultado_parcial();       // Vai para TELA_RESULTADO_PARCIAL e exibe placares.
    void tela_compras(int);         // Exibe o menu de compras de cada jogador

    // Métodos de interação com o usuário. São passados às funções do OpenGL
    // Estes métodos deveriam ser estáticos para poderem ser utilizados pelo
    // OpenGL.
    // Por outro lado, quando declaradas como funções estáticas, elas deixam de
    // fazer parte do objeto; dessa forma, não é mais possível acessá-lo com o
    // ponteiro this. Com isso, ela também não consegue mais acessar as proprie-
    // dades *não estáticas* do método.
    //
    // Ou seja, ela passa a funcionar como se fosse uma função declarada isola-
    // damente A única diferença é estar no escopo da classe Mundo.
    //
    // Portanto, eu mantive as funções em interacoes.hpp. A única coisa que elas
    // fazem ali é chamar as funções correspondentes do OBJETO GLOBAL mundo.
    // Dessa forma, eu consigo acesso às propriedades não estáticas.
    //
    // https://stackoverflow.com/questions/23774223/cannot-convert-classnameglutkeyboard-from-type-void-classnameunsigned
    void interacao_teclado(unsigned char tecla, int x, int y);
    void interacao_teclas_especiais(int key, int x, int y);
    void interacao_mouse(int botao, int estado, int x, int y);
    void funcao_exibicao();

private:
    Menu    *menu_ativo;            // Armazena o menu atualmente ativo
    Cenario *cenario;               // Armazena o cenário atual

};

#endif
