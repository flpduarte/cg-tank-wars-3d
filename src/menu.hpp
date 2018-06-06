/**
 * menu.cpp
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
struct EntradaMenu
{
    std::string titulo;
    int largura;
    int altura;
    virtual void desenhar() = 0;    // desenha o quadro centrado na origem
    virtual void reagir_a_tecla_especial(int tecla);
};

/**
 * Botao: Estrutura derivada de EntradaMenu.
 * Corresponde a um botão: ao selecioná-lo e apertar enter, ele executará
 * uma ação específica, definida ao criar o objeto.
 */
struct Botao : public EntradaMenu
{
    // ação que o botão executará é salva sob a forma de um ponteiro para uma
    // função a ser executada.
private:
    void (*acao)(void);

public:
    void desenhar();
    void reagir_a_tecla_especial();

    Botao(void ());
};

class Menu
{
    std::vector<EntradaMenu *> opcoes;
public:
    void exibir();
};
