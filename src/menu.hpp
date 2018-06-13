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
 * Declara as implementações da interface OpcaoMenu.
 */
#ifndef MENU_HPP
#define MENU_HPP
#include <vector>
#include <string>
#include "interfaces.hpp"
#include "constantes.hpp"

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

public:
    void desenhar();
    void reagir_a_teclado(unsigned char);  // Botões reagem à tecla Enter.

    Botao(std::string, void (void));
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
 */
class OpcaoAlterarValorNumerico : public OpcaoMenu
{
    int min;
    int max;
    int &referencia;

public:
    OpcaoAlterarValorNumerico(std::string, int, int, int &);
};



#endif
