//
// Created by Felipe on 09/01/2021.
//

#ifndef TANKWARS_PROJETIL_H
#define TANKWARS_PROJETIL_H

#include <cenario/Cenario.hpp>
#include <objetos/armas/Arma.h>

class Projetil;

/**
 * Representa um projétil em voo.
 * O Projétil é caracterizado por:
 *  - Arma disparada;
 *  - Cenário em que está imerso;
 *  - Condição inicial (x, y, z, vx, vy, vz).
 *
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
 * getMassaProjetil            = Massa do projétil. Para que a trajetória seja previsível,
 *                    todas as munições terão a mesma getMassaProjetil. Mantive esta proprie-
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
 *                        da potencia e do anguloCanhao dados. Comum para todos os projéteis.
 * atualizar_posicao()  = Atualiza a posição do projétil após um passo de tempo DT.
 * detonar()            = Efeito da munição ao atingir um obstáculo. (abstrato)
 *                        Classes derivadas devem implementar esta função.
 *
 */
class Projetil : public CenarioObject
{
    static constexpr double DT = 0.033;

    Arma *arma;
    double X[6];            // Variáveis de estado: [x, y, z, vx, vy, vz]
    double F[3];            // Componentes da força resultante sobre o projétil: [Fx, Fy, Fz]

    public:
    Projetil(Arma *arma, Cenario *cenario, const double X0[6]);

    double getRaio() const;             // Raio do projétil, para fins de detecção de colisão.
    double const *getPosicao() const;
    void atualizar_posicao();

    void desenhar() final;
    Explosao *detonar();        // produz a explosão da munição no local atual do projétil


private:
    // Equação diferencial de voo do projétil
    double derivada(int i);
};

#endif //TANKWARS_PROJETIL_H
