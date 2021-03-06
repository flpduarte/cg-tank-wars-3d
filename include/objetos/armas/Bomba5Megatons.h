//
// Created by Felipe on 11/01/2021.
//

#ifndef TANKWARS_BOMBA5MEGATONS_H
#define TANKWARS_BOMBA5MEGATONS_H


#include <objetos/armas/Arma.h>

/**
 * Bomba 5 Megatons: Dobro do raioProjetil da de 20 kilotons, a arma mais forte!
 */
class Bomba5Megatons : public Arma
{
    static constexpr char NOME[] = "Bomba 5 Megatons";
    static const int QUANTIDADE_INICIAL = 1;
    static const int PRECO_POR_LOTE = 10000;
    static const int QUANTIDADE_POR_LOTE = 1;

public:
    Bomba5Megatons();
    Explosao *detonar(double epicentro[3]) final;
};

#endif //TANKWARS_BOMBA5MEGATONS_H
