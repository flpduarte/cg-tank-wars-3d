//
// Created by Felipe on 11/01/2021.
//

#include <objetos/explosoes/BolaDeFogo.h>
#include "objetos/armas/Incinerador.h"

// constexpr precisam ser declarados no arquivo CPP para serem iniciados antes da chamada do construtor.
constexpr char Incinerador::NOME[];

/**
 * Incinerador: Armamento básico
 */
Incinerador::Incinerador() :
    Arma(NOME,
         PRECO_POR_LOTE,
         QUANTIDADE_POR_LOTE,
         QTD_INICIAL) {}

Explosao *Incinerador::detonar(double *epicentro) {
    return BolaDeFogo::ExplosaoIncinerador(epicentro);
}
