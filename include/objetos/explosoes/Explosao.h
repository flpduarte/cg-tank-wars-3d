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

/**
 * Explosao
 * Interface que gera o efeito terminal do armamento (danos aos tanques e quaisquer outros efeitos), bem como a sua
 * respectiva animação.
 *
 * Por enquanto, a única implementação desta interface é a classe BolaDeFogo.
 */
class Explosao
{
public:
    virtual int dano(double pos[3]) = 0;    // dada a posição de um jogador, retorna o dano causado pela explosão.
    virtual bool proximo_frame() = 0;       // Atualiza dados para desenhar o próximo "frame" da animação de explosão. Retorna false quando animação encerrar
    virtual void desenhar() = 0;            // Desenha o frame atual da explosão (coordenadas locais)


};

#endif
