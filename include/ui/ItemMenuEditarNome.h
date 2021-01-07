//
// Created by Felipe on 30/12/2020.
//

#ifndef TANKWARS_ITEMMENUEDITARNOME_H
#define TANKWARS_ITEMMENUEDITARNOME_H

#include <string>
#include <ui/ItemMenuRetangular.h>

/**
 * ItemMenuEditarNome
 * Cria uma classe de opção do menu no qual o título está relacionado a uma va-
 * riável string. Ela é utilizada para renomear jogadores. Pode também ser usado
 * para renomear outros objetos. Terá um formato parecido com este:
 *
 * +-------------------------------+
 * | Jogador 1                     |
 + +-------------------------------+
 *
 * Clicar Enter sobre a caixa muda a cor de seu fundo para um azul escuro e
 * apresenta um cursor à frente da última letra. O botão estará no modo edição,
 * e teclas normais do teclado modificarão o string título.
 *
 * Um segundo enter desativará o modo edição e salvará o string título na variá-
 * vel a que se refere o botão.
 *
 * O "modo edição" é implementado usando a propriedade de OpcaoMenu
 * bloqueia_cursor. Quando true, ela impede o cursor de mudar de posição com as
 * teclas para cima e para baixo. É o que se deseja fazer quando se estiver edi-
 * tando um nome.
 *
 * O botão terá um limite de número de caracteres, bem como aceitará somente
 * caracteres alfanumericos, espaços e backspace. Não aceitará tabs.
 *
 */
class ItemMenuEditarNome : public ItemMenuRetangular
{
    static const unsigned int MAX_CARACTERES_NOME = 15;
    string &referenciaAoNomeJogador;             // Quando o nome é editado aqui, o nome do objeto jogador também recebe a alteração.
    GLfloat const *cor_rotulo;

public:
    ItemMenuEditarNome(string &nomeJogador, GLfloat const *cor_rotulo);
    ~ItemMenuEditarNome() override;

    void desenhar() final;
    void reagir_a_teclado(unsigned char) final;


private:
    void imprimeTextoAlinhadoAEsqueda();
};

#endif //TANKWARS_ITEMMENUEDITARNOME_H
