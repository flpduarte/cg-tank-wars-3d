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
    /* Dimensões das Viewports durante as rodadas */
    static constexpr int VP3D_ALTURA      = JANELA_ALTURA - 100;   // 100 pixels p/ informações
    static constexpr int VP3D_LARGURA     = JANELA_LARGURA;
    static constexpr int VP3D_XMIN        = 0;
    static constexpr int VP3D_YMIN        = 0;

    /* Constantes da Cãmera */
    static constexpr double CAMERA_POS[]    = {50, -100, 50};
    static constexpr double CAMERA_LOOKAT[] = {50, 0, 23};
    static constexpr double CAMERA_VIEWUP[] = {0, 0, 1};

    /* Constantes da projeção perspectiva */
    static constexpr double FOV          = 40.0;
    static constexpr double ASPECT_RATIO = 1.3333; // 800 x 600
    static constexpr double DNEAR        = 50.;
    static constexpr double DFAR         = 500.;

    // Características da iluminação do sol
    static constexpr GLfloat SOMBRA[]      = {0.4f, 0.4f, 0.4f, 1.0f};
    static constexpr GLfloat POSICAO_SOL[4] = {-50.f, 0.f, 0.f, 1.f};
    static constexpr GLfloat COR_SOL[4]     = {0.8f, 0.8f, 0.8f, 1.0f};

    /* Características do texto na Viewport 2D */
    static constexpr float TAM_TEXTO            = 25.0f;
    static constexpr float ESPACAMENTO          = 5.0f;
    static constexpr float POS_PRIMEIRA_LINHA   = JANELA_ALTURA - ESPACAMENTO - TAM_TEXTO/2.f;    // coordenadas da janela
    static constexpr float POS_SEGUNDA_LINHA    = POS_PRIMEIRA_LINHA - TAM_TEXTO - ESPACAMENTO;
    static constexpr float POS_TERCEIRA_LINHA   = POS_SEGUNDA_LINHA - TAM_TEXTO - ESPACAMENTO;

    /* Propriedades */
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
    std::queue<int> fila_jogadores_mortos;

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

private:
    void posicionar();

};

// OBSERVAÇÕES SOBRE AS CONSTANTES ESTÁTICAS DA CLASSE:
//
// "Note that the constant initializer is not a definition. You still need to define the static member in an
// enclosing namespace."
// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr038.htm
//
// Resumindo, as expressões abaixo declaram, mas NÃO INICIAM, as constantes. Para iniciá-las, é preciso
// escrever o comando abaixo no 'namespace' (fora do bloco da classe):
//
// constexpr GLfloat SOMBRA[];
//
// Isso foi feito no arquivo .cpp.

#endif
