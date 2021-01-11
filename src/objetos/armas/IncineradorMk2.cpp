//
// Created by Felipe on 11/01/2021.
//

#include <objetos/explosoes/BolaDeFogo.h>
#include "objetos/armas/IncineradorMk2.h"

// constexpr precisam ser declarados no arquivo CPP para serem iniciados antes da chamada do construtor.
constexpr char IncineradorMk2::NOME[];

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
IncineradorMk2::IncineradorMk2() : Arma(
        NOME,
        PRECO_POR_LOTE,
        QUANTIDADE_POR_LOTE,
        QUANTIDADE_INICIAL
        )
{}

Explosao *IncineradorMk2::detonar(double *epicentro) {
    return BolaDeFogo::ExplosaoIncineradorMark2(epicentro);
}