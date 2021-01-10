/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Declara classes de munições a partir da interface Municao.
 * A primeira versão do jogo contém somente munições explosivas.
 */
#ifndef MUNICAO_HPP
#define MUNICAO_HPP

#include <string>

class Explosao;
class Projetil;

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
class Municao
{
public:
    double m;               // massa do armamento específico.
    double massa();

    std::string nome;       // Nome da arma.
    int preco;
    int qtd_por_lote;
    int qtd_inicial;        // Qtd que os jogadores possuem ao iniciar o jogo

    //Projetil *lancar(double pos[3], int power, int angle, int vento);
    virtual void desenhar() = 0;                // desenha munição em coordenadas do objeto
    virtual Explosao *detonar(double pos[3]) = 0;    // Realiza os efeitos da detonação da munição no local indicado
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
    Explosao *detonar(double [3]);  // Cria um objeto Explosao no local atual
                                // do armamento
    virtual void desenhar();    // Desenha um projétil padrão. Método pode ser
                                // substituído, se desejado.
};

#endif
