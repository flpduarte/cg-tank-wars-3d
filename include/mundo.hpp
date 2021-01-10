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
 * Classe Mundo: Gerencia o jogo: as telas possíveis do jogo (menu principal, cenario, placar, etc.) e o momento de
 * alternar entre as telas; armazena também as informações dos jogadores.
 *
 */
#ifndef MUNDO_HPP
#define MUNDO_HPP

#include <vector>

class Jogador;
class Menu;
class Cenario;

/**
 * Mundo: Contém as variáveis de estado do mundo tais como tela atual, no. de
 * jogadores, etc.
 *
 * Escrito como um Singleton, segundo as orientações daqui:
 * https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
 */
class Mundo
{
    // --- Procedimento para construir um Singleton ---
public:
    static Mundo &getInstance() {
        static Mundo instance;          // Static variable within a function: persists during the entire program.
        return instance;
    }

    // C++ 11: deletar métodos de copiar / assign que eventualmente poderiam criar uma cópia do singleton
    Mundo(Mundo const &) = delete;
    void operator=(Mundo const&) = delete;

    // Tornar construtor e destrutor privativos.
private:
    Mundo();
    ~Mundo();


    // --------- Restante da classe --------------
private:

    static const int MAX_JOGADORES = 10;

    enum TelaAtual {
        TELA_INICIAL,
        TELA_RENOMEAR_JOGADORES,
        TELA_RODADA,
        TELA_RESULTADO_PARCIAL,
        TELA_COMPRAS
    } tela_atual;

public:
    // Menu atual
    Menu    *menu_ativo;            // Armazena o menu atualmente ativo

    Jogador *jogadores[MAX_JOGADORES];              // Lista de jogadores.
    std::vector<Jogador *> jogadoresAtivos;         // Só estarão ativos os jogadores de 0 a n_jogadores - 1

    // configurações do jogo
    int n_jogadores;    // 2, ..., MAX_JOGADORES <= 10
    int n_rodadas;      // > 0

    // estado atual do mundo
    int rodada_atual;   // 1, 2, ..., n_rodadas
    Cenario *cenario;   // Armazena o cenário atual


    // Transição de telas de uma tela para outra e realizam o loop do jogo
    void ir_para_tela_inicial();            // Vai para a tela inicial
    void ir_para_tela_renomear_jogadores();      // TelaAtual inicial -> Escolha jogadores
    void iniciar_jogo();                    // Escolha jogadores -> jogo
    void iniciar_rodada();                  // Cria um novo cenário e inicia o loop de uma rodada_atual
    void ir_para_resultado_parcial();       // Vai para TELA_RESULTADO_PARCIAL e exibe placares ao fim de uma rodada
    void ir_para_tela_compras(int);         // Exibe o menu de compras de cada jogador

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
    /* Funções que criam os menus utilizados no jogo. (Transferido do arquivo configmenu.hpp / configmenu.cpp) */
    Menu *criar_menu_principal();
    Menu *criar_menu_renomear_jogadores();
    Menu *criar_menu_resultado_parcial();
    Menu *criar_menu_compras(Jogador *);
};

/**
 * As funções abaixo são utilizadas como callback em diversos objetos gerenciados pelo objeto Mundo. Para serem passadas
 * como argumento, elas não podem ser métodos não estáticos; ao invés disso, elas servem de wrapper para chamar o método
 * correspondente do objeto Mundo global.
 */
void tela_inicial();            // Vai para a tela inicial
void renomear_jogadores();      // TelaAtual inicial -> Escolha jogadores
void iniciar_jogo();            // Escolha jogadores -> jogo
void iniciar_rodada();          // Inicia o loop de uma rodada_atual
void resultado_parcial(int);    // Vai para TELA_RESULTADO_PARCIAL e exibe placares.
void tela_compras(unsigned int);// Exibe o menu de compras de cada jogador
#endif
