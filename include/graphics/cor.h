/**
 * Define o namespace corBase, ele contém algumas cores padrão.
 *
 * Created by Felipe on 30/01/2019.
 */

#ifndef TANKWARS_COR_H
#define TANKWARS_COR_H

#include <GL/gl.h>
#include <vector>

namespace cor
{
    const GLfloat PRETO[]    = {0, 0, 0, 1};
    const GLfloat VERMELHO[] = {1, 0, 0, 1};
    const GLfloat VERDE[]    = {0, 1, 0, 1};
    const GLfloat AZUL[]     = {0, 0, 1, 1};
    const GLfloat AMARELO[]  = {1, 1, 0, 1};
    const GLfloat CIANO[]    = {0, 1, 1, 1};
    const GLfloat LILAS[]    = {1, 0, 1, 1};
    const GLfloat BRANCO[]   = {1, 1, 1, 1};
    const GLfloat CINZA_MEDIO[] = {0.5, 0.5, 0.5, 1};
    const GLfloat CINZA_ESCURO[] = {0.2, 0.2, 0.2, 1};
    const GLfloat AZUL_CELESTE[] = {0, 0.66796875, 0.8984375, 1.0};
    const GLfloat LILAS_ESCURO[] = {0.5, 0, 0.5, 1};

    // Função auxiliar que copia os valores de corBase da variável origem à variável dest.
    void definir_cor(GLfloat *dest, const GLfloat *origem);
}

#endif //TANKWARS_COR_H
