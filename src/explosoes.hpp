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
#include "jogador.hpp"
/*
A linha abaixo provoca um problema de referências circulares no jogo:


O motivo é a sequência de includes:
explosoes.cpp -> explosoes.hpp -> jogador.hpp -> interfaces.hpp**

Em interfaces.hpp, a classe Jogador é solicitada *antes* de ter sido
definida.

Contudo, notamos que é o próprio header jogador.hpp que solicita o uso
de um header interfaces.hpp; o segundo por sua vez, necessita de jogador.hpp!

Para resolver esse problema, devemos verificar o que realmente precisamos:
 - Se só for preciso saber que uma classe existe, e não precisar *operar* sobre
   ela, ou seja, ela será utilizada exclusivamente na forma de ponteiros, então
   não é preciso fazer um #include no arquivo da classe. Uma simples DECLARAÇÃO
   de que a classe existe é suficiente.
 - Caso se necessite *operar* sobre a classe, ou seja, chamar as suas proprieda-
   des e/ou métodos, então aí sim devemos incluir seu Header.

Resumindo, se conhecer o interior da classe não for necessário, basta fazer um
forward declaration. Não é preciso - nem é recomendado - chamar o header file.
Isso normalmente ocorre em HEADER FILES: eles não operam sobre as classes, apenas
declaram funções que irão operá-las!

É isso que acontece nesse arquivo. Preciso apenas saber que existe uma classe
Jogador. Só quem precisa conhecer a estrutura interna da classe Jogador é
explosoes.cpp. explosoes.hpp pode apenas declarar a classe como mostrado a seguir.

*/
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
    // Constantes de iluminação
    const float fracao_sombra = 0.75;
    const float aten_quadratica = 0.1;

    // Características gerais da explosão
    double epicentro[3];
    double raio;
    int    t;                           // Tempo a contar do início da explosão.
    bool   finalizado;                  // Explosão finalizada

    // Variáveis utilizadas pelo método desenhar()
    double raio_atual;          // raio atual da bola de fogo
    GLfloat cor[4];              // cor atual da bola de fogo

    double dist(double [3], double [3]); // função auxiliar que calcula a distância entre 2 pontos

public:
    Explosao(double pos[3], double);    // Cria objeto explosão no local atual
    ~Explosao();                        // Destrutor da Explosao: desativa a fonte GL_LIGHT1.
    int dano(double pos[3]);            // dada a posição de um jogador, retorna o dano causado pela explosão.
    bool proximo_frame();               // Atualiza dados para desenhar o próximo "frame" da animação de explosão. Retorna false quando animação encerrar
    void desenhar();                    // Desenha a explosão
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
