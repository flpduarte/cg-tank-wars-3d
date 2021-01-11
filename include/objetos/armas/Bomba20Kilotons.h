//
// Created by Felipe on 11/01/2021.
//

#ifndef TANKWARS_BOMBA20KILOTONS_H
#define TANKWARS_BOMBA20KILOTONS_H


#include <array>
#include <objetos/armas/Arma.h>
/**
 * Bomba 20 kilotons: Dobro da forma do Mark II. Faz um estrago!
 */
class Bomba20Kilotons : public Arma
{
    static constexpr char NOME[] = "Bomba 20 Kilotons";
    static const int QUANTIDADE_INICIAL = 1;
    static const int PRECO_POR_LOTE = 7000;
    static const int QUANTIDADE_POR_LOTE = 2;
public:
    Bomba20Kilotons();
    Explosao *detonar(double epicentro[3]) final;
};

#endif //TANKWARS_BOMBA20KILOTONS_H
