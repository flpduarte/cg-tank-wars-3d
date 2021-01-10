//
// Created by Felipe on 28/01/2019.
//

#include <ui/ItemMenuBotao.h>
#include <constantes.hpp>
#include <GL/glut.h>
#include <objetos2D.hpp>
#include <utility>

/* --- Classe ItemMenuBotao --- */
/**
 * Inicia a classe Botão. Recebe como entrada uma função a ser chamada quando o
 * botão é apertado.
 *
 * Entradas:
 * - referenciaAoNomeJogador: título do botão
 * - fn : Ação a executar quando o botão é selecionado e Enter é pressionado.
 *
 * ItemMenuBotaoenuBotao(): função destrutora da classe botão; nada a fazer.
 */
ItemMenuBotao::ItemMenuBotao(std::string rotulo, void (fn)(), GLfloat const *cor_rotulo) :
        ItemMenuRetangular(), rotulo(std::move(rotulo)), acao(fn), cor_rotulo(cor_rotulo) {}

ItemMenuBotao::~ItemMenuBotao() = default;

/**
 * desenhar()
 * Desenha o botão na tela!
 */
void ItemMenuBotao::desenhar()
{
    desenharRetangulo();
    desenharTextoCentralizadoNoBotao();
}

void ItemMenuBotao::desenharTextoCentralizadoNoBotao() const {
    glPushMatrix();
    glTranslatef(largura / 2., altura / 2., 0);
    desenharTextoCentralizado(this->rotulo, 0.8 * altura, FONTE, this->cor_rotulo);
    glPopMatrix();
}

/**
 * reagir_a_teclado(tecla)
 * Quando o botão está selecionado e enter for pressionado, executa a função
 * gravada em this->acao.
 */
void ItemMenuBotao::reagir_a_teclado(unsigned char tecla)
{
    if ((tecla == '\n' || tecla == '\r') && this->selecionado)
    {
        this->acao();
    }
}
