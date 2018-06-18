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
 * // TODO - ainda em construção
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
    glEnable(GL_LIGHT0);

    // Configura projeção perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, ASPECT_RATIO, DNEAR, DFAR);

    // Muda para matriz ModelView e mantém-se nela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->posicionar();
}

/**
 * Destroi cenário após o fim da rodada
 */
Cenario::~Cenario()
{
    delete camera;
    delete terreno;
}

/**
 * Exibe o cenario na tela:
 * Cria viewport para exibir o cenario 3D
 * Sobre o cenario, cria um viewport 2D para exibir informações do jogador atual
 * No cenario 3D, mostrar:
 * - Terreno
 * - Tanques
 * - Tiro e Explosões, se for o caso.
 *
 * Note que aqui precisarei lidar com 2 viewports diferentes.
 *
 * Posso usar glScissor(left, bottom, width, height) para definir uma região em
 * Coordenadas da Tela que receberá desenhos. Isso permitirá limpar somente par-
 * te da tela, por exemplo. Usarei glScissor para limpar cada viewport com uma
 * cor diferente.
 *
 * Ideia:
 * 1. Definir o viewport inferior e desenhar o cenário 3D.
 * 2. Definir o viewport superior e desenhar as informações em 2D.
 * TODO!
 */
void Cenario::exibir()
{
    // TODO
    // limpa a tela
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //terreno->desenhar();
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
