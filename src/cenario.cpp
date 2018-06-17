/**
 * cenario.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 * Glauber Prado                    RA:
 *
 * Declara a classe Cenario: armazena as informações sobre o cenário
 * da rodada atual:
 * - Ordem em que os jogadores aparecem da esquerda para a direita;
 * - Posição da câmera
 * - Terreno atual
 * - etc.
 */
#include "cenario.hpp"

/* --- Implementação da classe Cenario --- */

/**
 * Cria um novo cenário: Terreno, câmera e ordem de aparecimento dos jogadores.
 */
Cenario::Cenario()
{
    // Cria câmera e terreno
    camera  = new Camera(CAMERA_POS, CAMERA_LOOKAT, CAMERA_VIEWUP);
    terreno = new Terreno;

    // Configura modelo de luz
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    

    // Iluminação do Sol.
    // Obs: Posso futuramente fazer essas configurações mudarem aleatoriamente,
    // para criar cenários noturnos, por exemplo. Mas isto está fora do escopo
    // do trabalho atual.
    glLightfv(GL_LIGHT0, GL_AMBIENT, SOMBRA); //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL); //contribuição difusa
	glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
}


/* --- Implementação da classe Camera --- */
Camera::Camera(const double p[3], const double la[3], const double vu[3])
{
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    look_at[0] = la[0];
    look_at[1] = la[1];
    look_at[2] = la[2];
    view_up[0] = vu[0];
    view_up[1] = vu[1];
    view_up[2] = vu[2];
}

void Camera::posicionar()
{
    gluLookAt(pos[0], pos[1], pos[2],
              look_at[0], look_at[1], look_at[2],
              view_up[0], view_up[1], view_up[2]);
}
