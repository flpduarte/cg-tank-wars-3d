/**
 * menu.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Define a classe Menu.
 * Cada objeto do tipo Menu conterá uma lista de botões e/ou opções
 * para serem exibidos na tela.
 *
 * Depois de configurados os objetos, o método .exibir() é utilizado
 * para desenhar os botões na tela.
 *
 * A função de interação com o teclado (teclas especiais) se comunica
 * com os objetos Menu e, de acordo com a tela ativa, envia o comando
 * ao respectivo o objeto. O objeto receberá o comando e, se necessário,
 * modificará suas propriedades (por exemplo, tecla para esquerda ou
 * direita serve para mudar o valor de alguma variável).
 */
#ifndef MENU_HPP
#define MENU_HPP
#include <vector>
#include <string>
#include "constantes.hpp"

/**
 * EntradaMenu: uma interface que corresponde aos tipos de opções e botões
 * que aparecem no menu.
 *
 * Toda entrada no menu possuirá um título e um método desenhar(), o qual
 * desenhará o quadro daquela entrada centrado na origem. Caberá ao objeto
 * Menu reposicionar o quadro.
 */
class OpcaoMenu
{
    std::string titulo;
    int largura;
    int altura;

public:
    OpcaoMenu(int largura, int altura, std::string titulo);  // construtor
    virtual void desenhar() = 0;                            // Virtual puro, classes filhas DEVEM implementá-lo.
    virtual void reagir_a_tecla_especial(int tecla) {}      // se não implementado, esta opção não reage a teclas especiais.
    virtual void reagir_a_teclado(unsigned char) {}         // se não implementado, esta opção de menu nao reage às teclas do teclado.
};

/**
 * Botao: Estrutura derivada de EntradaMenu.
 * Corresponde a um botão: ao selecioná-lo e apertar enter, ele executará
 * uma ação específica, definida ao criar o objeto.
 */
class Botao : public OpcaoMenu
{
    // ação que o botão executará é salva sob a forma de um ponteiro para uma
    // função a ser executada.
    void (*acao)(void);
    bool ativo;

public:
    void desenhar();
    void reagir_a_teclado(unsigned char);  // Botões reagem à tecla Enter.

    Botao(void (void), bool);
};


/**
 * Cria uma entrada do menu que permite alterar um valor com as teclas para
 * a esquerda ou para a direita. Algo do tipo:
 *
 * +-------------------------------+
 * | Número de jogadores: -  2  +  |
 + +-------------------------------+
 *
 * Tecla para a esquerda diminui até um mínimo, tecla para a direita aumenta
 * até um máximo.
 *
 * O valor a ser alterado é passado ao objeto *por referência*. Ou seja, ao al-
 * terar o seu valor na opção do menu, seu valor original será alterado - por ex.,
 * a variável n_jogadores.
 *
 * Por enquanto, este objeto só tem suporte a alterar valores numéricos.
 * TODO: como simplificar a criação destes objetos?
 */
class OpcaoAlterarValorNumerico : public OpcaoMenu
{
    int min;
    int max;
    int &referencia;

public:
    OpcaoAlterarValorNumerico(int, int, int &);
};

class Menu
{

    std::vector<OpcaoMenu *> opcoes;
    int opcao_ativa;                            // Opcao do menu atualmente ativa

public:
    void exibir();
    void gerenciar_teclado(int tecla);
    void gerenciar_teclas_especiais(int tecla);  // Tecla para cima e para baixo são gerenciados por Menu.
                                                 // As outras são jogadas para a entrada menu ativa.
};

#endif
