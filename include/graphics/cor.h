/**
 * Define o namespace cor, ele contém algumas cores padrão.
 *
 * Created by Felipe on 30/01/2019.
 */

#ifndef TANKWARS_COR_H
#define TANKWARS_COR_H

#include <GL/gl.h>

namespace cor
{
    const float PRETO[]    = {0, 0, 0, 1};
    const float VERMELHO[] = {1, 0, 0, 1};
    const float VERDE[]    = {0, 1, 0, 1};
    const float AZUL[]     = {0, 0, 1, 1};
    const float AMARELO[]  = {1, 1, 0, 1};
    const float CIANO[]    = {0, 1, 1, 1};
    const float LILAS[]    = {1, 0, 1, 1};
    const float BRANCO[]   = {1, 1, 1, 1};
    const float CINZA_MEDIO[] = {0.5, 0.5, 0.5, 1};
    const float CINZA_ESCURO[] = {0.2, 0.2, 0.2, 1};
    const float AZUL_CELESTE[] = {0, 0.66796875, 0.8984375, 1.0};
    const float LILAS_ESCURO[] = {0.5, 0, 0.5, 1};

    // Função auxiliar que copia os valores de cor da variável origem à variável dest.
    void definir_cor(GLfloat *dest, const GLfloat *origem);
}

#endif //TANKWARS_COR_H
