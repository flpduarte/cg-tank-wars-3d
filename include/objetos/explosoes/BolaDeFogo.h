//
// Created by Felipe on 10/01/2021.
//

#ifndef TANKWARS_BOLADEFOGO_H
#define TANKWARS_BOLADEFOGO_H

#include "objetos/explosoes/Explosao.h"

/**
 * BolaDeFogo
 * Explosão que provoca danos aos outros tanques.
 *
 * Efeito de explosão: exibe na tela o efeito de explosão a partir do epicentro dado.
 * Provoca danos nos tanques conforme modelo abaixo.
 *
 * Modelo de dano:
 *
 * 0                0.8R     1,4R
 * +-----------------|--------|------------>
 * Raio de explosão  | Raio de dano
 * Tanques dentro    | Tanques aqui sofrem dano parcial; cai linearmente
 * deste raioProjetil sofrem | com a distância a partir do raioProjetil de explosão.
 * 100% de dano      | Raio de dano = aprox. 125% do raioProjetil de explosão
 * configurado como  | (configurado como a constante FRACAO_EFEITO_COLATERAL)
 * FRACAO_RAIO_DANO
 */
class BolaDeFogo : public Explosao {

    // Raio de dano / Raio de Explosao no modelo de explosão
    static double constexpr FRACAO_RAIO_DANO = 0.8;
    static double constexpr FRACAO_EFEITO_COLATERAL = 1.4;

    // Constantes de iluminação
    static constexpr float FRACAO_SOMBRA = 0.75;
    static constexpr float ATENUACAO_QUADRATICA = 1.;

    int   frame_intervalos;

    // Características gerais da explosão
    double epicentro[3];
    double raio;
    int    t;
    bool   finalizado;

    // Variáveis utilizadas pelo método desenhar()
    double raio_atual;
    float cor[4];

public:
    // Bolas de fogo pré definidas:
    static BolaDeFogo *ExplosaoIncinerador(const double *epicentro);
    static BolaDeFogo *ExplosaoIncineradorMark2(const double *epicentro);
    static BolaDeFogo *Explosao20KilotonNuke(const double *epicentro);
    static BolaDeFogo *Explosao5MegatonNuke(const double *epicentro);

    // Métodos da classe
    BolaDeFogo(const double epicentro[3], double raio);
    ~BolaDeFogo();

    int dano(double pos[3]) override;    // dada a posição de um jogador, retorna o dano causado pela explosão.
    bool proximo_frame() override;       // Atualiza dados para desenhar o próximo "frame" da animação de explosão. Retorna false quando animação encerrar
    void desenhar() override;            // Desenha o frame atual da explosão (coordenadas locais)

private:
    static double distancia(double p1[3], double p2[3]);    // função auxiliar que calcula a distância entre 2 pontos
};


#endif //TANKWARS_BOLADEFOGO_H
