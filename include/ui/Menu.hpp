/**
 * menu.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Declara as implementações da interface OpcaoMenu.
 */
#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <ui/ItemMenu.h>

/**
 * Menu: Representa um Menu simples, com caixas de seleção e botões.
 * Cada opção será posicionada uma sobre a outra.
 *
 * Menu automaticamente posicionará cada opção em relação à origem.
 *
 * A origem do Menu é o seu *canto superior esquerdo*, e é dada em coorde-
 * nadas da tela. Menu parte do pressuposto de que a Janela de Recorte e a
 * Viewport ambas coincidem com o tamanho da janela.
 *
 * Quando posicionamento_automatico = true, a origem é recalculada a cada
 * inserção de linhas ao Menu, de forma que ela seja sempre exibida no centro
 * da tela. Isso pode ser modificado pelo método definir_origem().
 *
 * A manipulação dos objetos é feita pelo método exibir().
 *
 */
class Menu
{
    unsigned int largura, altura;               // dimensões totais do menu. Usado p/ centralizá-lo na tela
    int posx0, posy0;                         // Origem do Menu, Coordenadas da Tela
    vector<ItemMenu *> opcoes;
    unsigned int opcao_ativa;                            // Índice da opcao do menu atualmente ativa
    bool possui_opcao_selecionada;             // Um flag para indicar se o menu já possui uma opção->selecionado = true.
    bool posicionamento_automatico;

    void recalcular_origem();                   // Recalcula origem a partir da largura e altura totais

public:
    //Menu(int, int);                             // Recebe a origem do Menu como entrada
    Menu();
    ~Menu();                                    // Libera a memória usada pelas opções

    void definir_origem(int, int);              // Desativa posicionamento automático e define origem do menu
    void inserir_opcao(ItemMenu *);
    void exibir();
    void gerenciar_teclado(unsigned char);
    void gerenciar_teclas_especiais(int tecla);  // Tecla para cima e para baixo são gerenciados por Menu.
    // As outras são jogadas para a entrada menu ativa.
};

/**
 * QuadroInformativo
 * Define um quadro que apenas exibe informações e não é selecionável.
 *
 * Utilizado para exibir o resultado parcial.
 */
class QuadroInformativo
{

};

#endif
