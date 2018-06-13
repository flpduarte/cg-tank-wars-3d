/**
 * interfaces.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara as interfaces utilizadas pelo loop principal do jogo.
 */
#ifndef INTERFACES_HPP
#define INTERFACES_HPP
#include <string>
#include <vector>

/**
 * OpcaoMenu: uma interface que corresponde aos tipos de opções e botões
 * que aparecem no menu.
 *
 * Toda entrada no menu possuirá um título e um método desenhar(), o qual
 * desenhará o quadro daquela entrada centrado na origem. Caberá ao objeto
 * Menu reposicionar o quadro.
 *
 * Cada opção Menu é desenhado em coordenadas de objeto, com origem em seu
 * *canto inferior esquerdo*.
 */
class OpcaoMenu
{
public:
    int largura;
    int altura;
    std::string titulo;
    bool selecionado;     // Indica se o cursor encontra-se nesta opção.
    float cor_borda[3];
    float cor_fundo[3];
    float cor_titulo[3];

    OpcaoMenu(std::string titulo);                          // Cria objeto com altura e largura padrão. Pode ser modificado depois.
    virtual void desenhar() = 0;                            // Virtual puro, classes filhas DEVEM implementá-lo.
    virtual void reagir_a_tecla_especial(int tecla) {}      // se não implementado, esta opção não reage a teclas especiais.
    virtual void reagir_a_teclado(unsigned char) {}         // retorna true se precisar atualizar a tela após a ação.
};

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
 * A manipulação dos objetos é feita pelo método exibir().
 *
 */
class Menu
{
    int posx0, posy0;                           // Origem do Menu, Coordenadas da Tela
    std::vector<OpcaoMenu *> opcoes;
    unsigned int opcao_ativa;                   // Índice da opcao do menu atualmente ativa

public:
    Menu(int, int);                             // Recebe a origem do Menu como entrada
    void inserir_opcao(OpcaoMenu *);
    void exibir();
    void gerenciar_teclado(unsigned char);
    void gerenciar_teclas_especiais(int tecla);  // Tecla para cima e para baixo são gerenciados por Menu.
                                                 // As outras são jogadas para a entrada menu ativa.
};


/**
 * Municao: interface para munições. Cada munição implementada no jogo seguirá
 * esta interface.
 * Sistemas de Coordenadas do mundo:
 *
 * X: Alinhado norte-sul
 * Y: Alinhado leste-oeste; positivo para a esquerda (oeste)
 * Z: Vertical, positivo para cima.
 *
 * Nesta versão inicial do programa, o projétil se deslocará somente no plano XZ
 * do sistema de coordenadas do mundo.
 *
 * Propriedades
 * massa            = Massa do projétil. Para que a trajetória seja previsível,
 *                    todas as munições terão a mesma massa. Mantive esta proprie-
 *                    dade para o caso de eventualmente utilizar a interface para
 *                    outros tipos de projéteis, tal como o jogo original parece
 *                    fazer com a morte do tipo "Meltdown".
 * X[6]             = Vetor contendo as 6 variáveis de estado do projétil:
 *                    posX, posY, posZ, VelX, VelY, VelZ.
 * F[3]             = Vetor força resultante.
 *
 *
 * Métodos:
 * lancar()             = Lança o projétil. Em outras palavras, define as Coordenadas
 *                        de sua posicao inicial e define seu vetor velocidade a partir
 *                        da potencia e do angulo dados. Comum para todos os projéteis.
 * atualizar_posicao()  = Atualiza a posição do projétil após um passo de tempo DT.
 * detonar()            = Efeito da munição ao atingir um obstáculo. (abstrato)
 *                        Classes derivadas devem implementar esta função.
 *
 */
class Municao
{
    // Propredades da municao.
protected:
    std::string nome;       // Nome da arma
    double massa;           // Massa do projétil
    double X[6];            // Variáveis de estado: [x, y, z, vx, vy, vz]
    double F[3];            // Componentes da força resultante sobre o projétil.
                            // [Fx, Fy, Fz]

    double derivada(int i);

public:
    void lancar(int pos[3], int power, int angle, int vento);
    void atualizar_posicao();
    virtual void detonar() = 0;
};
#endif
