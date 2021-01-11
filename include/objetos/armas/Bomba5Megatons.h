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
    static constexpr char NOME[] = "Incinerador Mark II";
    static const int QUANTIDADE_INICIAL = 2;
    static const int PRECO_POR_LOTE = 4000;
    static const int QUANTIDADE_POR_LOTE = 10;

public:
    Bomba5Megatons();
    Explosao *detonar(double epicentro[3]) final;
};

#endif //TANKWARS_BOMBA5MEGATONS_H
