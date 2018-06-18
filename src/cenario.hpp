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
#ifndef CENARIO_HPP
#define CENARIO_HPP

#include <vector>
#include <GL/glut.h>
#include "jogador.hpp"
#include "terreno.hpp"

struct Camera;

class Cenario
{
    /* Constantes */
    /* Constantes da Cãmera */
    const double CAMERA_POS[3]    = {50, -100, 50};
    const double CAMERA_LOOKAT[3] = {50, 0, 23};
    const double CAMERA_VIEWUP[3] = {0, 0, 1};

    /* Constantes da projeção perspectiva */
    const double FOV          = 40.0;
    const double ASPECT_RATIO = 1.3333; // 800 x 600
    const double DNEAR        = 50;
    const double DFAR         = 500;

    /* Características da iluminação do sol */
    const GLfloat SOMBRA[4]      = {0.4f, 0.4f, 0.4f, 1.0f};
    const GLfloat POSICAO_SOL[4] = {-50, 0, 0, 1};
    const GLfloat COR_SOL[4]     = {1.0f, 1.0f, 1.0f,1.0f};

    /* Propriedades */
    Camera  *camera;                    // Camera principal
    Terreno *terreno;                   // Terreno atual
    std::vector<Jogador *> jogadores;   // Lista dos jogadores em ordem aleatória

public:
    Cenario();
    ~Cenario();

    void exibir();                      // Exibe o cenário atual na tela
};

/* Agrupamento das informações da câmera em uma estrutura */
struct Camera
{
	double pos[3];
	double look_at[3];
	double view_up[3];

	Camera(const double p[3], const double la[3], const double vu[3]);
	void posicionar();
};
#endif
