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
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "cenario.hpp"
#include "constantes.hpp"
#include "globals.hpp"

/* --- Implementação da classe Cenario --- */

/**
 * Cria um novo cenário: Terreno, câmera e ordem de aparecimento dos jogadores.
 * // TODO - ainda em construção
 */
Cenario::Cenario()
{
    // Cria câmera e terreno
    camera   = new Camera(CAMERA_POS, CAMERA_LOOKAT, CAMERA_VIEWUP);
    terreno  = new Terreno;
    projetil = NULL;

    // Configura iluminação do Sol.
    // Obs: Posso futuramente fazer essas configurações mudarem aleatoriamente,
    // para criar cenários noturnos, por exemplo. Mas isto está fora do escopo
    // do trabalho atual.
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, SOMBRA);           //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL);          //contribuição difusa
	glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    // Cria lista aleatória de jogadores
    jogadores = new Jogador *[mundo.n_jogadores]();
    misturar_jogadores();
    posicionar_jogadores();
}

/**
 * Destroi cenário após o fim da rodada
 */
Cenario::~Cenario()
{
    delete camera;
    delete terreno;
}

/* --- Funções privadas --- */
/**
 * Mistura a ordem de aparecimento dos jogadores e define suas respectivas
 * posições no cenário
 */
void Cenario::misturar_jogadores()
{
    srand(time(NULL));

    // lê jogadores em ordem "aleatória"
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        // Procura um jogador que ainda não existe na lista
        int n;
        do
        {
            n = rand() % mundo.n_jogadores;
        } while (existe_elemento(jogadores, i, mundo.jogadores[n]));

        // Insere-o no final da lista
        jogadores[i] = mundo.jogadores[n];
    }
}


/**
 * Após definir a ordem em que os jogadores aparecem, distribuí-los sobre o
 * terreno.
 *
 * Posicionamento:
 * - primeiro jogador:x = 10; (pode variar entre 8 e 12)
 * - último jogador:  x = 90;
 *
 * Restante dos jogadores é posicionado uniformemente num intervalo de 80.
 *
 * J1 ----- J2 ----- J3 ------ J4 ------ J5
 *
 * Passo = (n_jogadores - 1) / 80
 */
void Cenario::posicionar_jogadores()
{
    double passo = 80. / (mundo.n_jogadores - 1);
    double x0    = (double) 8 + rand() % 4;

    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        double x = x0 + i*passo;
        double pos[3] = {x, 0, terreno->z(x, 0)};
        jogadores[i]->posicionar(pos);
        jogadores[i]->definir_normal(terreno->normal(x, 0));
    }

    // ajusta ângulo inicial dos canhoes dos jogadores nas extremidades
    jogadores[0]->angulo = 75;
    jogadores[mundo.n_jogadores - 1]->angulo = 105;
}

/**
 * Retorna true se o jogador dado pertence ao array dado.
 * Retorna false, caso contrário.
 */
bool Cenario::existe_elemento(Jogador **lista, int n, Jogador *jogador)
{
    bool existe = false;
    for (int i = 0; !existe && (i < n); i++)
    {
        existe = (lista[i] == jogador);
    }

    return existe;
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
 * 1. Desenhar as informações em 2D na tela, antes de exibir cenário 3D.
 *    Deve-se garantir que não haverá conflitos entre os dados 2D e o cenário 3D.
 * 2. Definir o viewport 3D e desenhar o cenário.
 */
void Cenario::exibir()
{
    desenhar_na_viewport2D();
    desenhar_na_viewport3D();
}

/**
 * Desenha o cenário 3D!
 * Hipótese: informações 2D já foram desenhadas na tela.
 */
void Cenario::desenhar_na_viewport3D()
{
    // Configura GL_SCISSOR para coincidir com viewport para limpar a tela com
    // cor azul celeste
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);    // não desenha polígonos encobertoss por outros à sua frente

    // Pintar viewport de azul celeste
    glScissor(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(cor::AZUL_CELESTE[0], cor::AZUL_CELESTE[1], cor::AZUL_CELESTE[2], cor::AZUL_CELESTE[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Muda para matriz ModelView e mantém-se nela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->posicionar();

    // Configura Viewport e Projeção Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, ASPECT_RATIO, DNEAR, DFAR);
    //glViewport(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);

    // Ativa efeitos de iluminação e desenha o terreno
    glMatrixMode(GL_MODELVIEW);
    terreno->desenhar();

    // Desenha os jogadores
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        jogadores[i]->desenhar();
    }

    // Desenha o projétil, se houver
    if (projetil != NULL)
    {
        projetil->desenhar();
    }
}

/**
 * Desenha as informações sobre a imagem 3D:
 * - Vento, angulo, potencia, arma atual, etc.
 *
 * As informações são exibidas antes de exibir o cenário em 3D. Em outras pala-
 * vras, o cenário 3D é desenhado sobre as informações 2D. Considerei o viewport
 * 2D como sendo a tela inteira; tomar cuidado para não exibir nenhuma informação
 * onde depois será posicionado a viewport 3D.
 */
void Cenario::desenhar_na_viewport2D()
{
    // Limpa a tela para preto. Assume que Scissor está desligado.
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // TODO: imprimir as informações
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
