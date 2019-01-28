//
// Created by Felipe on 10/01/2019.
//

#include <string>
#include <ui/ItemMenu.h>
#include <GL/glut.h>

using namespace std;

/* --- Implementação do construtor de ItemMenu --- */
/**
 * Cria um objeto OpcaoMenu com largura e altura padrões.
 */
ItemMenu::ItemMenu(std::string tit):
        largura(ITEM_MENU_LARGURA_PADRAO),
        altura(ITEM_MENU_ALTURA_PADRAO),
        titulo(tit),
        selecionavel(true),
        selecionado(false),
        bloqueia_cursor(false)
{
    // define cores padrão
    cor::definir_cor(cor_borda, cor::BRANCO);
    cor::definir_cor(cor_fundo, cor::PRETO);
    cor::definir_cor(cor_titulo, cor::BRANCO);
}

/* É estranho, mas é preciso definir o destrutor */
ItemMenu::~ItemMenu() {}

/* Reações padrão às funções reagir_a_tecla_especial() e reagir_a_teclado() */
void ItemMenu::reagir_a_teclado(unsigned char tecla) {}
void ItemMenu::reagir_a_tecla_especial(int tecla) {}


/**
 * Desenha a borda de um quadro de menu.
 */
void ItemMenu::desenhar_borda(const unsigned int largura, const unsigned int altura, const float cor[4])
{
    glColor4fv(cor);
    glLineWidth(ITEM_MENU_LARGURA_BORDA);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(largura, 0, 0);
    glVertex3f(largura, altura, 0);
    glVertex3f(0, altura, 0);
    glEnd();
}

///* --- Implementação do construtor de ItemMenu --- */
///**
// * Cria um objeto OpcaoMenu com largura e altura padrões.
// */
//ItemMenu::ItemMenu(std::string tit):
//        largura(LARGURA_PADRAO),
//        altura(OPCAOMENU_ALTURA_PADRAO),
//        titulo(tit),
//        selecionavel(true),
//        selecionado(false),
//        bloqueia_cursor(false)
//{
//    // define cores padrão
//    cor::definir_cor(cor_borda, cor::BRANCO);
//    cor::definir_cor(cor_fundo, cor::PRETO);
//    cor::definir_cor(cor_titulo, cor::BRANCO);
//}
//
///* É estranho, mas é preciso definir o destrutor */
//ItemMenu::~ItemMenu() {}
//
///* Reações padrão às funções reagir_a_tecla_especial() e reagir_a_teclado() */
//void ItemMenu::reagir_a_teclado(unsigned char tecla) {}
//void ItemMenu::reagir_a_tecla_especial(int tecla) {}
