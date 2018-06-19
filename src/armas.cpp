/**
 * armas.cpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Implementa cada tipo de munição declarada em armas.hpp
 */
#include <iostream>
#include "globals.hpp"
#include "constantes.hpp"
#include "armas.hpp"

/**
 * Cria a lista global de armamentos. Chamado no início do jogo (bomb.cpp)
 */
void criar_lista_global_armamentos()
{
    armamentos[0] = MunicaoEQtd(new Incinerador);
    armamentos[1] = MunicaoEQtd(new IncineradorM2);
    armamentos[2] = MunicaoEQtd(new Bomba20Kilotons);
    armamentos[3] = MunicaoEQtd(new Bomba5Megatons);
}

/* --- implementa as funções das classes MunicaoEQtd e ListaArmamentos --- */
// constructor padrão: cria um elemento vazio
MunicaoEQtd::MunicaoEQtd():
    arma(NULL), qtd(0) {}

// construtor usado ao criar a lista global: armazena munição e quantidade por lote
// Entrada: apenas munição
MunicaoEQtd::MunicaoEQtd(Municao *mun):
    arma(mun), qtd(mun->qtd_por_lote) {}


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
        lista[i] = armamentos[i];
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
    while (lista[++i_atual].qtd <= 0);
}

/**
 * Retorna o armamento ativo
 */
Municao *ListaArmamentos::arma_atual()
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
 * Decrementa 1 qtd da arma ativa. Esta função é chamada quando a arma é lançada.
 * Note que esta função não troca o armamento ativo. A verificação se ainda há
 * tiros do armamento ativo deve ser realizada ao iniciar a vez do jogador.
 */
void ListaArmamentos::decrementa_municao()
{
    lista[i_atual].qtd--;
}


/**
 * Restaura a lista de armamentos para a condição inicial, ou seja,
 * ajusta todas as quantidades para seus valores padrão.
 */
void ListaArmamentos::condicao_inicial()
{
    for (int i = 0; i < N_ARMAMENTOS; i++)
    {
        lista[i].qtd = lista[i].arma->qtd_inicial;
    }
    i_atual = 0;
}


/* ---- Implementação dos armamentos ---- */
// TODO: Definir constantes para todos os valores:
// preço, qtd por lote, qtd inicial, etc.
/**
 * Incinerador: Armamento básico
 */
Incinerador::Incinerador()
{
    this->nome         = "Incinerador";
    this->preco        = 3000;
    this->qtd_por_lote = 100;
    this->qtd_inicial  = QTD_INCINERADOR;
    this->r_explosao   = RAIO_INCINERADOR;
}
int Incinerador::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
IncineradorM2::IncineradorM2()
{
    this->nome         = "Incinerador Mark II";
    this->preco        = 4000;
    this->qtd_por_lote = 10;
    this->qtd_inicial  = 0;
    this->r_explosao   = 2*RAIO_INCINERADOR;
}
int IncineradorM2::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
Bomba20Kilotons::Bomba20Kilotons()
{
    this->nome         = "Bomba 20 Kilotons";
    this->preco        = 7000;
    this->qtd_por_lote = 2;
    this->qtd_inicial  = 0;
    this->r_explosao   = 4*RAIO_INCINERADOR;
}
int Bomba20Kilotons::raio_explosao()
{
    return this->r_explosao;
}

/**
 * Bomba 5 Megatons: Dobro do raio da de 20 kilotons, a arma mais forte!
 */
Bomba5Megatons::Bomba5Megatons()
{
    this->nome         = "Bomba 5 Megatons";
    this->preco        = 10000;
    this->qtd_por_lote = 1;
    this->qtd_inicial  = 0;
    this->r_explosao   = 8*RAIO_INCINERADOR;
}
int Bomba5Megatons::raio_explosao()
{
    return this->r_explosao;
}
