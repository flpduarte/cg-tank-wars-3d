//
// Created by Felipe on 30/01/2019.
//

#include <graphics/cor.h>

/**
 * Copia valores de corBase de origem para dest.
 *
 */
void cor::definir_cor(GLfloat *dest, const GLfloat *origem)
{
    for (int i = 0; i < 4; i++)
    {
        dest[i] = origem[i];
    }
}