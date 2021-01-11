//
// Created by Felipe on 11/01/2021.
//

#ifndef TANKWARS_INCINERADORMK2_H
#define TANKWARS_INCINERADORMK2_H

#include <objetos/armas/Arma.h>

/**
 * Incinerador Mark II: dobro da força do incinerador.
 */
class IncineradorMk2 : public Arma
{
    static constexpr char NOME[] = "Incinerador Mark II";
    static const int QUANTIDADE_INICIAL = 2;
    static const int PRECO_POR_LOTE = 4000;
    static const int QUANTIDADE_POR_LOTE = 10;
public:
    IncineradorMk2();
    Explosao *detonar(double epicentro[3]) final;
};

#endif //TANKWARS_INCINERADORMK2_H
