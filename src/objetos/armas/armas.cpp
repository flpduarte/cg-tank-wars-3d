/**
 * armas.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa cada tipo de munição declarada em armas.hpp
 */
#include <iostream>
#include "objetos/armas/armas.hpp"
#include "globals.hpp"
#include <objetos/armas/Incinerador.h>
#include <objetos/armas/IncineradorMk2.h>
#include <objetos/armas/Bomba20Kilotons.h>
#include <objetos/armas/Bomba5Megatons.h>


/**
 * Cria a lista global de armamentos. Chamado no início do jogo (bomb.cpp)
 */
void criar_lista_global_armamentos()
{
    lista_global_armamentos[0] = MunicaoEQtd(new Incinerador);
    lista_global_armamentos[1] = MunicaoEQtd(new IncineradorMk2);
    lista_global_armamentos[2] = MunicaoEQtd(new Bomba20Kilotons);
    lista_global_armamentos[3] = MunicaoEQtd(new Bomba5Megatons);
}

/* --- implementa as funções das classes MunicaoEQtd e ListaArmamentos --- */
// constructor padrão: cria um elemento vazio
MunicaoEQtd::MunicaoEQtd():
    arma(NULL), qtd(0) {}

// construtor usado ao criar a lista global: armazena munição e quantidade por lote
// Entrada: apenas munição
MunicaoEQtd::MunicaoEQtd(Arma *mun):
    arma(mun), qtd(mun->quantidadePorLote) {}


/**
 * Define operador = para uso com MunicaoEQtd
 */
void MunicaoEQtd::operator=(MunicaoEQtd referencia)
{
    this->arma = referencia.arma;
    this->qtd  = referencia.qtd;
}


/* ------------ ListaArmamentos -------------- */

/**
 * (IMPORTANTE)
 * Cria a lista de todos os armamentos existentes no jogo, usando a lista global
 * 'armamentos' como referência.
 */
ListaArmamentos::ListaArmamentos()
{
    // Copia a lista de armamentos global
    for (int i = 0; i < N_ARMAMENTOS; i++)
    {
        lista[i] = lista_global_armamentos[i];
    }

    // Define o armamento atual como sendo o de índice 0
    i_atual = 0;
}


/**
 * selecionar_proxima(): seleciona o próximo armamento disponível
 */
void ListaArmamentos::selecionar_proxima()
{
    // incrementa i até encontrar um armamento com qtd > 0.
    do
    {
        i_atual = (i_atual + 1) % N_ARMAMENTOS;
    }
    while (lista[i_atual].qtd <= 0);
}

/**
 * Retorna o armamento ativo
 */
Arma *ListaArmamentos::arma_atual()
{
    return lista[i_atual].arma;
}


/**
 * Retorna a quantidade de tiros da arma ativa
 */
int ListaArmamentos::qtd_atual()
{
    return lista[i_atual].qtd;
}


/**
 * Adiciona uma qtd específica de tiros da arma especificada pelo indice.
 */
void ListaArmamentos::adicionar_lote(int indice, int qtd)
{
    lista[indice].qtd += qtd;
}

/**
 * Retira uma qtd específica de tiros da arma especificada pelo índice.
 * Não fazer nada se a remoção fizesse com que a quantidade se tornasse negativa
 */
void ListaArmamentos::remover_lote(int indice, int qtd)
{
    if (lista[indice].qtd - qtd >= 0)
        lista[indice].qtd -= qtd;
}

/**
 * Decrementa 1 qtd da arma ativa e retorna o ponteiro para a arma.
 * Esta função é chamada quando a arma é lançada.
 * Note que esta função não troca o armamento ativo. A verificação se ainda há
 * tiros do armamento ativo deve ser realizada ao iniciar a vez do jogador.
 */
Arma *ListaArmamentos::atirarArmaAtual()
{
    lista[i_atual].qtd--;
    return lista[i_atual].arma;
}


/**
 * Restaura a lista de armamentos para a condição inicial, ou seja,
 * ajusta todas as quantidades para seus valores padrão.
 */
void ListaArmamentos::condicao_inicial()
{
    for (int i = 0; i < N_ARMAMENTOS; i++)
    {
        lista[i].qtd = lista[i].arma->quantidadeInicial;
    }
    i_atual = 0;
}