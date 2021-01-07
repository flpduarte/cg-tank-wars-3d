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
#include <ui/ItemMenu.h>
#include "constantes.hpp"


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
class Explosao;
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
    virtual Explosao *detonar(double pos[3]) = 0;    // Realiza os efeitos da detonação da munição no local indicado
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
    void atualizar_posicao();
    bool atingiu_obstaculo();   // Retorna true se o projétil atingiu um obstáculo - tanque ou terra

    void desenhar();
    Explosao *detonar();        // produz a explosão da munição no local atual do projétil
};


#endif
