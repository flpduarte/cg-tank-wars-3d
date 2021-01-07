//
// Created by Felipe on 30/12/2020.
//

#include "objetos2D.hpp"
#include "constantes.hpp"
#include <graphics/cor.h>
#include <GL/glut.h>
#include "interfaces.hpp"
#include "ui/ItemMenuEditarNome.h"

/**
 * Construtor e destrutor
 */
ItemMenuEditarNome::ItemMenuEditarNome(string &nomeJogador, GLfloat const *cor_rotulo):
        ItemMenuRetangular(), referenciaAoNomeJogador(nomeJogador), cor_rotulo(cor_rotulo) {}

ItemMenuEditarNome::~ItemMenuEditarNome() = default;

/**
 * Reagir a teclado: para permitir edição do nome
 */
void ItemMenuEditarNome::reagir_a_teclado(unsigned char tecla)
{
    // Se não estiver no modo edição, reage apenas a enter.
    if (!bloqueia_cursor)
    {
        if ((tecla == '\n') || (tecla == '\r'))
        {
            bloqueia_cursor = true;
        }
    }

    // Quando modo edição estiver ativo, permitir digitar!
    else
    {
        // Enter: desativa modo edição e salva string na referência
        if ((tecla == '\n') || (tecla == '\r'))
        {
            bloqueia_cursor = false;
            //referenciaAoNomeJogador = titulo;
        }

        // Backspace: apaga o último caractere - enquanto existirem caracteres
        else if ((tecla == '\b') && !referenciaAoNomeJogador.empty())
        {
            referenciaAoNomeJogador.pop_back();
        }

        // Teclas alfanuméricas e espaço: Acrescenta ao string
        else if ((isalnum(tecla) || tecla == ' ') && referenciaAoNomeJogador.size() < MAX_CARACTERES_NOME)
        {
            referenciaAoNomeJogador += tecla;
        }

        // Ignora todas as outras teclas
    }
}

/**
 * Desenha o quadro da opção de editar nome
 */
void ItemMenuEditarNome::desenhar()
{
    desenharRetangulo();
    imprimeTextoAlinhadoAEsqueda();
}

void ItemMenuEditarNome::imprimeTextoAlinhadoAEsqueda() {
    glPushMatrix();
    glTranslatef(10., altura / 2., 0.);
    desenhar_string(bloqueia_cursor ? referenciaAoNomeJogador + "|" : referenciaAoNomeJogador, 4. * altura / 5., FONTE, cor_rotulo);
    glPopMatrix();
}

