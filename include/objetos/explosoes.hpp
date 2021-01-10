/**
 * explosoes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Declara as funções que realizam os efeito de detonação.
 * Inicialmente conterá somente explosão;
 * No futuro, será incluso aqui a produção de terra (Ball of Dirt).
 */
#ifndef EXPLOSOES_HPP
#define EXPLOSOES_HPP



class Jogador;

/**
 * Explosao
 * Classe que representa uma explosão!
 * Especificamente, é responsável por desenhar a animação da explosão,
 * bem como "avisar" à classe Cenario quando a animação encerrar.
 *
 * Efeito de explosão: exibe na tela o efeito de explosão a partir do epicentro
 * dado.
 * Provoca danos nos tanques conforme modelo abaixo.
 *
 * Modelo de dano:
 *
 * +-----------------|--------|------------>
 * Raio de explosão  | Raio de dano
 * Tanques dentro    | Tanques aqui sofrem dano parcial; cai linearmente
 * deste raio sofrem | com a distância a partir do raio de explosão.
 * 100% de dano      | Raio de dano = aprox. 125% do raio de explosão
 *                   | (configurado como a constante FRACAO_RAIO_DANO)
 */

class Explosao
{
    static double constexpr FRACAO_RAIO_DANO = 0.8;
    static double constexpr FRACAO_EFEITO_COLATERAL = 1.4;    // Raio de dano / Raio de Explosao no modelo de explosão

    // Constantes de iluminação
    static constexpr float FRACAO_SOMBRA = 0.75;
    static constexpr float ATENUACAO_QUADRATICA = 1.;
    int   frame_intervalos;             // controla velocidade de explosao

    // Características gerais da explosão
    double epicentro[3];
    double raio;
    int    t;                           // Tempo a contar do início da explosão.
    bool   finalizado;                  // Explosão finalizada

    // Variáveis utilizadas pelo método desenhar()
    double raio_atual;          // raio atual da bola de fogo
    GLfloat cor[4];              // corBase atual da bola de fogo

public:
    Explosao(const double posicao[3], double raio);    // Cria objeto explosão no local atual
    ~Explosao();                        // Destrutor da Explosao: desativa a fonte GL_LIGHT1.
    int dano(double pos[3]);            // dada a posição de um jogador, retorna o dano causado pela explosão.
    bool proximo_frame();               // Atualiza dados para desenhar o próximo "frame" da animação de explosão. Retorna false quando animação encerrar
    void desenhar();                    // Desenha a explosão

private:
    double distancia(double p1[3], double p2[3]); // função auxiliar que calcula a distância entre 2 pontos
};

/**
 * Efeito de explosão: exibe na tela o efeito de explosão a partir do epicentro
 * dado.
 * Provoca danos nos tanques conforme modelo abaixo
 *
 * Modelo de dano:
 *
 * +-----------------|--------|------------>
 * Raio de explosão  | Raio de dano
 * Tanques dentro    | Tanques aqui sofrem dano parcial; cai linearmente
 * deste raio sofrem | com a distância a partir do raio de explosão.
 * 100% de dano      | Raio de dano = aprox. 125% do raio de explosão
 *                   | (configurado como a constante FRACAO_RAIO_DANOa)
 */

#endif
