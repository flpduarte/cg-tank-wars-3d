//
// Created by Felipe on 11/01/2021.
//

#include "objetos/armas/Bomba5Megatons.h"
#include <objetos/explosoes/BolaDeFogo.h>

// constexpr precisam ser declarados no arquivo CPP para serem iniciados antes da chamada do construtor.
constexpr char Bomba5Megatons::NOME[];

/**
 * Bomba 5 Megatons: Dobro do raioProjetil da de 20 kilotons, a arma mais forte!
 */
Bomba5Megatons::Bomba5Megatons(): Arma(
        NOME,
        PRECO_POR_LOTE,
        QUANTIDADE_POR_LOTE,
        QUANTIDADE_INICIAL
) {}

Explosao *Bomba5Megatons::detonar(double *epicentro) {
    return BolaDeFogo::Explosao5MegatonNuke(epicentro);
}