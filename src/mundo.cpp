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
 * Implementa as funções definidas em mundo.hpp
 *
 */

// para desativar asserts, ativar este comando antes de #define <cassert>
//#define NDEBUG
#include <GL/glut.h>
#include <cassert>
#include <iostream>
#include <objetos/armas.hpp>
#include <objetos/jogador.hpp>
#include <cenario.hpp>
#include <mundo.hpp>
#include <ui/Menu.hpp>
#include <ui/ItemMenuAlterarValorNumerico.h>
#include <ui/ItemMenuBotao.h>
#include <ui/ItemMenuEditarNome.h>


/* Funções auxiliares */

/**
 * Deixa a tela preta e ajusta janela de recorte de forma que as Coordenadas do
 * Mundo coincidam com as Coordenadas da TelaAtual.
 */
void preparar_tela_para_menu()
{
    // Limpa a tela
    glClear(GL_COLOR_BUFFER_BIT);

    // Configura janela de recorte 2D para fazer coordenadas do mundo coincidir
    // com as coordenadas da tela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, JANELA_LARGURA, 0, JANELA_ALTURA);

    // inicia matriz model-view para exibir menu
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Cria o mundo ao iniciar o jogo.
 */
Mundo::Mundo()
{
    // Cria lista global de armamentos
    criar_lista_global_armamentos();

    // Inicia os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogadores[i] = new Jogador(i + 1);
    }

    // Configurações padrão
    this->tela_atual  = TELA_INICIAL;
    this->n_jogadores = PADRAO_N_JOGADORES;
    this->n_rodadas   = PADRAO_N_RODADAS;
    this->rodada_atual = -1;
    this->menu_ativo  = nullptr;
    this->cenario     = nullptr;
}

/**
 * Destroi o mundo ao final do jogo
 */
Mundo::~Mundo()
{
    for (auto & jogador : this->jogadores) {
        delete jogador;
    }
}

/**
 * Transiciona para a tela inicial
 */
void Mundo::ir_para_tela_inicial()
{
    // Muda a tela atual
    this->tela_atual = TELA_INICIAL;

    // Configura a tela do menu principal
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);         // funcionalidade q permite desenhar em apenas parte da tela
    glClearColor(0, 0, 0, 0);

    // Apaga menu antigo e cria menu novo
    delete this->menu_ativo;
    this->menu_ativo = criar_menu_principal();

    // Avisa que é preciso redesenhar a tela.
    // Isto provoca uma chamada ao glutDisplayFunc.
    glutPostRedisplay();
}


/**
 * Transiciona para a tela de renomear jogadores.
 * Não é preciso mudar configurações de exibição: isto já foi feito para o menu
 * principal.
 */
void Mundo::ir_para_tela_renomear_jogadores()
{
    // Muda a tela atual
    this->tela_atual = TELA_RENOMEAR_JOGADORES;

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_renomear_jogadores();
    glutPostRedisplay();
}

/**
 * Configura o mundo para iniciar o jogo
 */
void Mundo::iniciar_jogo()
{
    // Zera todas as variáveis do jogo
    jogadoresAtivos.clear();
    for (int i = 0; i < n_jogadores; i++)
    {
        jogadores[i]->resetar_jogador();
        jogadoresAtivos.emplace_back(jogadores[i]);
    }

    // Inicia a primeira rodada
    rodada_atual = 0;
    this->iniciar_rodada();
}

/**
 * Inicia a rodada - configura o cenário
 */
void Mundo::iniciar_rodada()
{
    // Espera-se que o cenário deva estar desativado
    assert(cenario == nullptr);

    // Muda a tela ativa
    this->tela_atual = TELA_RODADA;

    // Remove menus da memória
    if (this->menu_ativo != nullptr)
    {
        delete this->menu_ativo;
        this->menu_ativo = nullptr;
    }

    // Prepara para início da rodada
    rodada_atual++;
    cenario = new Cenario(jogadoresAtivos);
    glutPostRedisplay();
}


/**
 * Exibe a tela de resultados parciais.
 * O incremento do número de vitórias deve ter sido feito ao finalizar a rodada,
 * imediatamente antes de chamar esta função.
 */
void Mundo::ir_para_resultado_parcial()
{
    // Remove cenário
    if (this->cenario != NULL)
    {
        delete this->cenario;
        this->cenario = NULL;
    }

    // Transiciona para a tela de resultado parcial
    this->tela_atual = TELA_RESULTADO_PARCIAL;

    // Configura a tela de resultado parcial
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0, 0);

    // Apaga menu antigo e cria menu novo
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }
    this->menu_ativo = criar_menu_resultado_parcial();
    glutPostRedisplay();
}


/**
 * Exibe o menu de compras para cada jogador.
 * Entrada: número do jogador: 1, 2, ..., n_jogadores
 */
void Mundo::ir_para_tela_compras(int njogador)
{
    // Transiciona para a tela de compras. Usa as mesmas Configurações
    // que a tela de resultado parcial.
    this->tela_atual = TELA_COMPRAS;
    if (this->menu_ativo != NULL)
    {
        delete this->menu_ativo;
    }

    // Enquanto njogador for um jogador válido, exibe menu de compras
    if (njogador <= this->n_jogadores)
    {
        this->menu_ativo = criar_menu_compras(jogadores[njogador - 1]);
        glutPostRedisplay();
    }

    // Senão, inicia a próxima rodada
    else
    {
        this->iniciar_rodada();
    }
}

/* --- Funções de interação com o usuário --- */

/**
 * Função responsável pela exibição dos itens na tela. É provavelmente a principal
 * função do jogo.
 *
 * Exibe os elementos na tela de acordo com cada estado do jogo.
 */
void Mundo::funcao_exibicao()
{
    switch (this->tela_atual)
    {
        // Exibe menu principal na tela inicial
        case TELA_INICIAL:
        case TELA_RESULTADO_PARCIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_COMPRAS:
            preparar_tela_para_menu();
            this->menu_ativo->exibir();
            break;

        // Exibe o cenário
        case TELA_RODADA:
            this->cenario->exibir();
            break;
    }

    // redesenha a tela
    glFlush();
}


/**
 * Descreve a interação do usuário com o teclado, conforme cada estado do jogo.
 */
void Mundo::interacao_teclado(unsigned char tecla, int x, int y)
{
    switch (this->tela_atual)
    {
        case TELA_INICIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_RESULTADO_PARCIAL:
        case TELA_COMPRAS:
            this->menu_ativo->gerenciar_teclado(tecla);
            break;

        case TELA_RODADA:
            this->cenario->gerenciar_teclado(tecla);
            break;
    }
    glutPostRedisplay();
}


/**
 * Descreve a interação com as teclas especiais em cada parte do jogo, se houver.
 */
void Mundo::interacao_teclas_especiais(int tecla, int x, int y)
{
    switch (this->tela_atual)
    {
        case TELA_INICIAL:
        case TELA_RENOMEAR_JOGADORES:
        case TELA_RESULTADO_PARCIAL:
        case TELA_COMPRAS:
            this->menu_ativo->gerenciar_teclas_especiais(tecla);
            break;

        case TELA_RODADA:
            this->cenario->gerenciar_teclas_especiais(tecla);
            break;

    }
    glutPostRedisplay();
}


/**
 * Descreve a interação com o mouse conforme cada parte do jogo.
 * (deixei aqui para lembrar, mas talvez nem seja necessária)
 */
void Mundo::interacao_mouse(int botao, int estado, int x, int y)
{
    switch (tela_atual)
    {
        case TELA_INICIAL:
        // TODO
        break;

        case TELA_RENOMEAR_JOGADORES:
        // TODO
        break;

        case TELA_RODADA:
        // TODO
        break;

        case TELA_RESULTADO_PARCIAL:
        // TODO
        break;

        case TELA_COMPRAS:
        // TODO
        break;
    }
}


/* ---- Métodos para criação dos menus do jogo ---- */

/**
 * Cria um menu principal. Retorna o ponteiro para o objeto Menu.
 */
Menu* Mundo::criar_menu_principal()
{
    Menu *menu = new Menu;
    Mundo &mundo = Mundo::getInstance();

    // adiciona opções
    menu->inserir_opcao(new ItemMenuAlterarValorNumerico("Numero de Rodadas", 1, 100, mundo.n_rodadas));
    menu->inserir_opcao(new ItemMenuAlterarValorNumerico("Numero de Jogadores", 2, Mundo::MAX_JOGADORES, mundo.n_jogadores));
    menu->inserir_opcao(new ItemMenuBotao("INICIAR", renomear_jogadores));
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
Menu* Mundo::criar_menu_renomear_jogadores()
{
    Menu *menu = new Menu();

    // Insere as opções de renomear cada jogador
    for (int i = 0; i < n_jogadores; i++)
    {
        ItemMenuEditarNome *nova = new ItemMenuEditarNome(jogadores[i]->nome, jogadores[i]->corBase);
        menu->inserir_opcao(nova);
    }

    // Insere botões INICIAR e voltar
    // Obs: para chamar uma função global com o mesmo nome de uma função dentro da classe: basta preceder o nome da função
    // por "::" - ou seja, a função está localizado no namespace anônimo.
    // https://stackoverflow.com/questions/18107094/call-global-function-with-same-name-as-class-method/18107296
    // TODO: Verificar a possibilidade de referenciar diretamente aos métodos da classe.
    menu->inserir_opcao(new ItemMenuBotao("INICIAR JOGO", ::iniciar_jogo));  // Chama iniciar_jogo() de interacoes.hpp.
    menu->inserir_opcao(new ItemMenuBotao("Voltar", tela_inicial));
    return menu;
}

/**
 *
 */
Menu* Mundo::criar_menu_resultado_parcial()
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
Menu* Mundo::criar_menu_compras(Jogador *)
{
    // TODO
    return new Menu();
}


/* --- Implementação das funções usadas como callback, localizadas fora da classe Mundo --- */

/**
 * Vai para a tela inicial do jogo.
 * Chega-se nessa tela:
 * - Ao iniciar o jogo
 * - Ao clicar voltar da tela de renomear jogadores;
 * - Ao terminar um jogo.
 */
void tela_inicial()
{
    Mundo::getInstance().ir_para_tela_inicial();
}

/**
 * Transiciona para a tela de renomear jogadores. Executado após clicar "INICIAR"
 * na tela inicial.
 */
void renomear_jogadores()
{
    Mundo::getInstance().ir_para_tela_renomear_jogadores();
}

/**
 * Executa as ações de iniciar um jogo do zero. Executada após clicar "INICIAR"
 * na tela de renomear os jogadores.
 */
void iniciar_jogo()
{
    Mundo::getInstance().iniciar_jogo();
}

/**
 * Inicia o loop de uma rodada atual
 */
void iniciar_rodada()
{
    Mundo::getInstance().iniciar_rodada();
}

/**
 * Apresenta a tela de resultados parciais, após o término de uma rodada.
 * É chamada por um glutTimerFunc(), daí a necessidade da entrada, mesmo não sendo usada.
 */
void resultado_parcial(int valor)
{
    Mundo::getInstance().ir_para_resultado_parcial();
}

/**
 * Apresenta o menu contendo os itens que o jogador pode comprar.
 * Recebe como entrada o número do jogador. Deve ser executado com cada jogador
 * ativo.
 */
void tela_compras(unsigned int jogador)
{
    Mundo::getInstance().ir_para_tela_compras(jogador);
}
