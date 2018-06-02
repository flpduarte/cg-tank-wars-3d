/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara a interface para munições. Armamentos individuais implementarão
 * esta interface.
 *
 * Sistemas de Coordenadas do mundo:
 *
 * X: Alinhado norte-sul
 * Y: Alinhado leste-oeste; positivo para a esquerda (oeste)
 * Z: Vertical, positivo para cima.
 *
 * Nesta versão inicial do programa, o projétil se deslocará somente no plano XZ
 * do sistema de coordenadas do mundo.
 */

/**
 * Municao: interface para munições. Cada munição implementada no jogo seguirá
 * esta interface.
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


/**
 * Define uma classe de munições explosivas, ou seja, detonam quando atingem
 * o solo ou um tanque.
 *
 * Nota: cada detalhamento de uma munição do tipo MunicaoExplosiva deve definir
 * o seu próprio raio_explosao.
 */
class MunicaoExplosiva : public Municao
{
protected:
    virtual int raio_explosao() = 0; // declarada como método virtual para
                                        // forçar a implementação por classes filhas
public:
    MunicaoExplosiva();         // Construtor define a massa do projétil.
    void detonar();             // Executa o efeito de explosão no local atual
                                // do armamento
};
