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
 * Implementa os métodos da classe Jogador.
 *
 */
#include <string>
#include <iostream>
#include "constantes.hpp"
#include "armas.hpp"
#include "jogador.hpp"

void definir_cor(float *, const int);     // função local para definir a cor do tanque

/**
 * Cria um novo jogador.
 * Entrada: número do jogador: 1, 2, ..., MAX_JOGADORES.
 */
Jogador::Jogador(int i): njogador(i)
{
    // define a cor do tanque:
    definir_cor(this->cor, i);
    this->nome = "Jogador " + std::to_string(i);
    this->pontos = 0;
    this->dolares = 0;
    this->lista_municoes = nova_lista_municoes();

    this->homens = 100;
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->angulo = 90;
    this->potencia = 200;
}

/**
 * Libera a memória utilizada pelo objeto Jogador
 */
Jogador::~Jogador()
{
    // TODO: apagar lista_municoes. Preciso ajudar a função nova_lista_municoes(),
    // que está criando a lista sem fornecer o seu tamanho.
}

/**
 * Define a cor do tanque de acordo com o número do jogador.
 * A definição da cor segue a mesma sequência que no Tank Wars original.
 * A alteração da cor é realizada por referência.
 */
void definir_cor(float *cor, const int i)
{
    switch (i)
    {
        case 1:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.;
        break;

        case 2:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 3:
        cor[0] = 0.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 4:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 5:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 6:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 7:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 8:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.;
        break;

        case 9:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.5;
        break;

        case 10:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.5;
        break;
    }
}

/* ------------------------- */
/* Funções auxiliares        */

/**
 * Dado um TipoMunicao, retorna um novo objeto correspondente ao tipo recebido.
 */
Municao *obter_objeto_municao(TipoMunicao tipo)
{
    switch (tipo)
    {
        case INCINERADOR:
            return new Incinerador;

        case INCINERADORM2:
            return new IncineradorM2;

        case BOMBA20KILOTONS:
            return new Bomba20Kilotons;

        case BOMBA5MEGATONS:
            return new Bomba5Megatons;

        default:
            std::cerr << "Tipo de municao nao esperada - obter_objeto_municao()." << std::endl;
            exit(-1);
    }
}

/**
 * nova_lista_municoes(): retorna uma lista de estruturas MunicaoEQtd, contendo
 * todas as municoes existentes no jogo, porém com quantidades = 0 (exceto incinerador).
 */
MunicaoEQtd *nova_lista_municoes()
{
    MunicaoEQtd *lista = new MunicaoEQtd[N_ARMAMENTOS];
    for (int i = 0; i < N_ARMAMENTOS; i++)
    {
        lista->tipo = (TipoMunicao) i;
        lista->qtd  = (i == INCINERADOR) ? QTD_INCINERADOR : 0;
    }
    return lista;
}
