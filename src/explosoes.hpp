/**
 * explosoes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara as funções que realizam os efeito de detonação.
 * Inicialmente conterá somente explosão;
 * No futuro, será incluso aqui a produção de terra (Ball of Dirt).
 */
#ifndef EXPLOSOES_HPP
#define EXPLOSOES_HPP

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
void efeito_explosao(int epicentro[3], int raio_explosao);

#endif
