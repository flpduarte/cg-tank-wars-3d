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
 * Declara classes de munições a partir da interface Arma.
 * A primeira versão do jogo contém somente munições explosivas.
 */
#ifndef MUNICAO_HPP
#define MUNICAO_HPP

#include <string>

class Explosao;
class Projetil;

/**
 * Arma: Representa as características de uma munição:
 * - Massa (por enquanto, todas constantes)
 * - nome
 * - preço
 * - quantidade adquirida por lote
 *
 * Interface:
 * - desenhar: Desenha o projétil correspondente à arma atual. O desenho é feito
 *             em coordenadas do corpo; transladá-lo posteriormente para o mundo.
 * - detonar(): Desenha o efeito de detonação da munição, incluindo animação. Deve
 *              ser transladado para o local onde se localiza o objeto Projetil.
 */
class Arma
{
    static constexpr double MASSA_PADRAO = 1.0;

    static constexpr double m = MASSA_PADRAO;

    // Constantes referentes ao desenho do projétil padrão (esfera prateada)
public:
    static constexpr float COR_PROJETIL[]        = {0.4, 0.4, 0.4, 1.0};
    static constexpr float SPECULAR_PROJETIL[]   = {0.75, 0.75, 0.75, 0.75};
    static constexpr float BRILHO_PROJETIL       = 20.0f;
    static constexpr double RAIO_PADRAO_PROJETIL = 4*1/32. * 3.0;

public:
    // Propriedades físicas de um projétil da arma
    const double massaProjetil;                 // Cálculo da trajetória
    const double raioProjetil;                  // Detecção de colisão

    // Informações da arma
    const std::string nome;
    const int preco;
    const int quantidadePorLote;
    const int quantidadeInicial;        // Qtd que os jogadores possuem ao iniciar o jogo

    Arma(std::string nome, int preco, int qtdPorLote, int qtdInicial, double massaProjetil = MASSA_PADRAO, double raioProjetil = RAIO_PADRAO_PROJETIL);

    double getRaioProjetil() const;
    double getMassaProjetil() const;

    virtual void desenhar();                // Desenha o projétil correspondente ao armamento. Já possui uma implementação, que desenha uma esfera prateada.
    virtual Explosao *detonar(double pos[3]) = 0;    // Realiza os efeitos da detonação da munição no local indicado
};

#endif
