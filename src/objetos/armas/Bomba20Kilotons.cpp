//
// Created by Felipe on 11/01/2021.
//

#include <objetos/armas/Bomba20Kilotons.h>
#include <objetos/explosoes/BolaDeFogo.h>

// constexpr precisam ser declarados no arquivo CPP para serem iniciados antes da chamada do construtor.
constexpr char Bomba20Kilotons::NOME[];

/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
Bomba20Kilotons::Bomba20Kilotons() :
    Arma(NOME,
        PRECO_POR_LOTE,
        QUANTIDADE_POR_LOTE,
         QUANTIDADE_INICIAL
    ) {}

Explosao *Bomba20Kilotons::detonar(double *epicentro) {
    return BolaDeFogo::Explosao20KilotonNuke(epicentro);
}