/**
 * interfaces.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
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
    unsigned int largura;
    unsigned int altura;
    std::string titulo;
    bool selecionavel;      // Indica se o quadro é selecionavel ou não.
    bool selecionado;       // Indica se o cursor encontra-se nesta opção.

    bool bloqueia_cursor;   // Um estado que indica se ele impede a mudança para
                            // outras opções por meio das setas para cima e para baixo

    // cores em RGBA
    float cor_borda[4];
    float cor_fundo[4];
    float cor_titulo[4];

    OpcaoMenu(std::string titulo);                          // Cria objeto com altura e largura padrão. Pode ser modificado depois.
    virtual ~OpcaoMenu() = 0;                               // Obriga classes filhas a definirem um destrutor
    virtual void desenhar() = 0;                            // Virtual puro, classes filhas DEVEM implementá-lo.
    virtual void reagir_a_tecla_especial(int tecla);        // se não implementado, esta opção não reage a teclas especiais.
    virtual void reagir_a_teclado(unsigned char);           // retorna true se precisar atualizar a tela após a ação.
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
    std::vector<OpcaoMenu *> opcoes;
    unsigned int opcao_ativa;                            // Índice da opcao do menu atualmente ativa
    bool _possui_opcao_selecionada;             // Um flag para indicar se o menu já possui uma opção->selecionado = true.
    bool posicionamento_automatico;

    void recalcular_origem();                   // Recalcula origem a partir da largura e altura totais

public:
    //Menu(int, int);                             // Recebe a origem do Menu como entrada
    Menu();
    ~Menu();                                    // Libera a memória usada pelas opções
    void definir_origem(int, int);              // Desativa posicionamento automático e define origem do menu
    void inserir_opcao(OpcaoMenu *);
    void exibir();
    void gerenciar_teclado(unsigned char);
    void gerenciar_teclas_especiais(int tecla);  // Tecla para cima e para baixo são gerenciados por Menu.
                                                 // As outras são jogadas para a entrada menu ativa.
};


/**
 * Municao: Representa as características de uma munição:
 * - Massa (por enquanto, todas constantes)
 * - nome
 * - preço
 * - quantidade adquirida por lote
 *
 * Interface:
 * - desenhar: Desenha o projétil correspondente à munição atual. O desenho é
 *             em coordenadas do objeto; transladá-lo posteriormente para o mundo.
 * - lançar  : Cria um objeto Projetil, o qual é responsável pelos cálculos ba-
 *             lísticos. O objeto carregará as características da municção atual.
 * - detonar(): Desenha o efeito de detonação da munição, incluindo animação. Deve
 *              ser transladado para o local onde se localiza o objeto Projetil.
 */
class Projetil;
class Municao
{
    // Propredades da municao.
public:
    double m;               // massa do armamento específico.
    double massa();

    std::string nome;       // Nome da arma.
    int preco;
    int qtd_por_lote;
    int qtd_inicial;        // Qtd que os jogadores possuem ao iniciar o jogo

    Projetil *lancar(double pos[3], int power, int angle, int vento);
    virtual void desenhar() = 0;                // desenha munição em coordenadas do objeto
    virtual void detonar(double pos[3]) = 0;    // Realiza os efeitos da detonação da munição no local indicado
};

/**
 * Representa uma munição *em voo*.
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
class Projetil
{
    Municao *municao;
    double X[6];            // Variáveis de estado: [x, y, z, vx, vy, vz]
    double F[3];            // Componentes da força resultante sobre o projétil.
                            // [Fx, Fy, Fz]
    double derivada(int);

    public:
    Projetil(Municao *m, double X0[6], int vento);
    void desenhar();
    void atualizar_posicao();
    bool atingiu_obstaculo();   // Retorna true se o projétil atingiu um obstáculo - tanque ou terra
};


#endif
