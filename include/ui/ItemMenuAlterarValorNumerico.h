//
// Created by Felipe on 30/12/2020.
//

#ifndef TANKWARS_ITEMMENUALTERARVALORNUMERICO_H
#define TANKWARS_ITEMMENUALTERARVALORNUMERICO_H

#include <string>
#include <ui/ItemMenuRetangular.h>

/**
 * ItemMenuAlterarValorNumerico
 * Cria uma opção do menu que permite alterar um valor com as teclas para
 * a esquerda ou para a direita. Algo do tipo:
 *
 * +-------------------------------+
 * | Número de jogadores: -  2  +  |
 + +-------------------------------+
 *
 * Tecla para a esquerda diminui até um mínimo, tecla para a direita aumenta
 * até um máximo.
 *
 * O valor a ser alterado é passado ao objeto *por referência*. Ou seja, ao al-
 * terar o seu valor na opção do menu, seu valor original será alterado - por ex.,
 * a variável n_jogadores.
 *
 * Por enquanto, este objeto só tem suporte a alterar valores numéricos.
 */
class ItemMenuAlterarValorNumerico : public ItemMenuRetangular
{
    int min;
    int max;
    int &referencia;
    GLfloat const *cor_referencia;
    string const rotulo;
    // GLfloat const cor_rotulo;

public:
    ItemMenuAlterarValorNumerico(string rotulo, int valorMinimo, int valorMaximo, int &referenciaAoValorAlterado);
    ~ItemMenuAlterarValorNumerico();

    void reagir_a_tecla_especial(int tecla);    // reage às teclas esquerda e direita
    void desenhar();

private:
    void desenharTextoDoBotao();
};

#endif //TANKWARS_ITEMMENUALTERARVALORNUMERICO_H
