//
// Created by Felipe on 30/12/2020.
//

#include <ui/ItemMenuEditarNome.h>
#include <objetos2D.hpp>
#include <constantes.hpp>
#include <GL/glut.h>
#include <ui/ItemMenuAlterarValorNumerico.h>

ItemMenuAlterarValorNumerico::ItemMenuAlterarValorNumerico(string rotulo, int valorMinimo, int valorMaximo, int &referenciaAoValorAlterado):
        ItemMenuRetangular(), rotulo(std::move(rotulo)), min(valorMinimo), max(valorMaximo), referencia(referenciaAoValorAlterado), cor_referencia(cor::VERDE)
{}

ItemMenuAlterarValorNumerico::~ItemMenuAlterarValorNumerico() = default;

/**
 * Reação a teclas especiais: reage à seta esquerda ou direita.
 * Esquerda: diminui o valor
 * Direita : aumenta o valor
 */
void ItemMenuAlterarValorNumerico::reagir_a_tecla_especial(int tecla)
{
    switch (tecla)
    {
        case (GLUT_KEY_LEFT):
            if (this->referencia > this->min)
                this->referencia--;
            break;

        case (GLUT_KEY_RIGHT):
            if (this->referencia < this->max)
                this->referencia++;
            break;
    }
}

/**
 * Desenha o quadro
 */
void ItemMenuAlterarValorNumerico::desenhar()
{
    desenharRetangulo();
    desenharTextoDoBotao();

}

void ItemMenuAlterarValorNumerico::desenharTextoDoBotao() {// Escrever texto
    string texto = rotulo + ": - " + to_string(referencia) + " +";
    glPushMatrix();
    glTranslatef(largura / 2., altura / 2., 0);
    desenharTextoCentralizado(texto, 0.8 * altura, FONTE, cor_referencia);
    glPopMatrix();
}
