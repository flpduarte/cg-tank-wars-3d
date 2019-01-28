/**
 * cenario.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
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
#include <queue>
#include <GL/glut.h>
#include "constantes.hpp"

class Terreno;
class Jogador;
class Explosao;
class Projetil;
struct Camera;

class Cenario
{
    /* Constantes da Cãmera */
    const double CAMERA_POS[3]    = {50, -100, 50};
    const double CAMERA_LOOKAT[3] = {50, 0, 23};
    const double CAMERA_VIEWUP[3] = {0, 0, 1};

    /* Constantes da projeção perspectiva */
    const double FOV          = 40.0;
    const double ASPECT_RATIO = 1.3333; // 800 x 600
    const double DNEAR        = 50.;
    const double DFAR         = 500.;

    /* Características da iluminação do sol */
    const GLfloat SOMBRA[4]      = {0.4f, 0.4f, 0.4f, 1.0f};
    const GLfloat POSICAO_SOL[4] = {-50., 0., 0., 1.};
    const GLfloat COR_SOL[4]     = {0.8f, 0.8f, 0.8f, 1.0f};

    /* Características do texto na Viewport 2D */
    const float TAM_TEXTO            = 25.0f;
    const float ESPACAMENTO          = 5.0f;
    const float POS_PRIMEIRA_LINHA   = JANELA_ALTURA - ESPACAMENTO - TAM_TEXTO/2.;    // coordenadas da janela
    const float POS_SEGUNDA_LINHA    = POS_PRIMEIRA_LINHA - TAM_TEXTO - ESPACAMENTO;
    const float POS_TERCEIRA_LINHA   = POS_SEGUNDA_LINHA - TAM_TEXTO - ESPACAMENTO;

    /* Propriedades */
    Camera  *camera;                    // Camera principal
    Terreno *terreno;                   // Terreno atual
    Jogador **jogadores;                // Lista dos jogadores em ordem aleatória
    int      n_jogadores_vivos;         // Guarda o número de jogadores vivos.
    Projetil *projetil;                 // Projétil em voo
    Explosao *explosao;                 // Explosão atualmente ocorrendo
    Jogador  *jogador_morrendo;         // Armazena o jogador cuja animação de morte está atualmente sendo executada.
    int vento;                          // Vento no cenário atual. + para dir.
    int jog_vez;                        // De quem é a vez: 0, 1, 2, ...
    int jog_ativo;                      // É um pouco diferente da variável vez.
                                        // jogador_ativo indica o jogador a ser
                                        // mostrado no topo da página. Essa exibição
                                        // mostra, por exemplo, qual foi o jogador
                                        // que 'morreu'.
    bool controle_jogador;              // Estado do cenário: true = não responde ao jogador; true = jogador no controle.

    // Funções para exibir o cenário
public:
    Cenario();
    ~Cenario();
    void criar_explosao(double pos[3], double raio);
    void exibir();                      // Exibe o cenário atual na tela
    void gerenciar_teclado(unsigned char);
    void gerenciar_teclas_especiais(int);
    double z_solo(double x, double y);      // Retorna a coordenada z do solo em (x, y)

private:
    int  definir_vento();               // Define vento conforme configurações do jogo
    void misturar_jogadores();
    void posicionar_jogadores();
    void desenhar_na_viewport2D();      // Configura VP 2D e desenha informações
    void desenhar_na_viewport3D();      // Configura VP 3D e desenha cenário
    void desenhar();                    // Desenha o cenário em si: terreno, jogadores, projéteis, explosões, etc.

    bool existe_elemento(Jogador **, int, Jogador *);    // verifica se um jogador pertence à lista


    /* Funções responsáveis pelo loop do cenário */
public:
    // funções para uso com glutTimerFunc()
    static void animacao_projetil(int);      // Função timer do cenário para animar o projétil
    static void animacao_explosao(int);      // Função timer do cenário para animar as explosões
    static void animacao_morte_jogador(int); // Função timer do cenário para animar as explosões

    void animar_projetil();                 // Responsável por animar o projétil
    void animar_explosao();                 // Responsável por animar uma explosão
    void animar_morte_jogador();            // Responsável por animar a morte do jogador.
    void analisar_danos();                  // Responsável por atualizar os efeitos provocados pelas explosões
    void retirar_jogadores_mortos();        // Responsável por executar a animação de cada jogador "marcado para morrer" e atualizar num. de jogadores vivos
    bool rodada_encerrou();                 // Responsável por informar se a rodada acabou (1 ou 0 jogadores vivos) e atualizar num vitorias do vencedor
    void iniciar_vez_do_proximo_jogador();  // Responsável por iniciar a vez do próximo jogador vivo.

    // Variáveis auxiliares do loop
private:
    std::queue<int> fila_jogadores_mortos;
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
