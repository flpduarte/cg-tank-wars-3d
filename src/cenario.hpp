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
    const double CAMERA_POS[3]    = {50, 100, 80};
    const double CAMERA_LOOKAT[3] = {50, 0, 20};
    const double CAMERA_VIEWUP[3] = {0, 0, 1};

    /* Características da iluminação do sol */
    const GLfloat SOMBRA[4] = {0.6f, 0.6f, 0.6f, 1.0f};
    const GLfloat POSICAO_SOL[4] = {-150, 50, 200, 1};
    const GLfloat COR_SOL[4] = {1.0f, 1.0f, 1.0f,1.0f};

    /* Propriedades */
    Camera  *camera;                    // Camera principal
    Terreno *terreno;                   // Terreno atual
    std::vector<Jogador *> jogadores;   // Lista dos jogadores em ordem aleatória

public:
    Cenario();
    ~Cenario();
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
