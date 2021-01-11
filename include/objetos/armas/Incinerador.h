//
// Created by Felipe on 11/01/2021.
//

#ifndef TANKWARS_INCINERADOR_H
#define TANKWARS_INCINERADOR_H

#include <objetos/armas/Arma.h>

/**
 * Incinerador: Armamento básico
 */
class Incinerador : public Arma
{
    static constexpr char NOME[] = "Incinerador";
    static const int QTD_INICIAL = 100;     // Qtd inicial de incineradores por jogador - armas.cpp
    static const int PRECO_POR_LOTE = 3000;
    static const int QUANTIDADE_POR_LOTE = 100;
public:
    Incinerador();
    Explosao *detonar(double epicentro[3]) final;
};



#endif //TANKWARS_INCINERADOR_H
