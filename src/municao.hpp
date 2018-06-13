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
 * Declara classes de munições a partir da interface Municao.
 * A primeira versão do jogo contém somente munições explosivas.
 */
#ifndef MUNICAO_HPP
#define MUNICAO_HPP
#include "interfaces.hpp"

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


#endif
