//
// Created by Felipe on 10/01/2021.
//

#include "cenario/CenarioObject.h"

unsigned int CenarioObject::proximoId = 1;

CenarioObject::CenarioObject(bool visivelInicialmente) : visivel(visivelInicialmente), id(proximoId++) {}

unsigned int CenarioObject::getInt() const {
    return id;
}
