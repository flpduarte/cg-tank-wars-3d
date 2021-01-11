//
// Created by Felipe on 10/01/2021.
//


#ifndef TANKWARS_CENARIOOBJECT_H
#define TANKWARS_CENARIOOBJECT_H

/**
 * CenarioObject: Classe base para todos os objetos que aparecem no cenário: tanques, explosões, terreno e quaisquer
 * outros objetos futuros.
 *
 * Esta classe dá a cada objeto criado um id único, para ser usado como chave na lista de CenarioObject e permitir que
 * seja localizado rapidamente.
 */
class CenarioObject {

    // id do objeto para servir de chave, quando usado em um set.
    static unsigned int proximoId;
    const unsigned int id;

public:
    // Objetos do cenário são normalmente visíveis quando criados
    explicit CenarioObject(bool visivelInicialmente = true);
    unsigned int getInt() const;

    bool visivel;
    virtual void desenhar() = 0;
};


#endif //TANKWARS_CENARIOOBJECT_H
