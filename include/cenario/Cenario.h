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
#include <random>
#include <cenario/Tanque.h>
#include <GL/glut.h>
#include <set>
#include "constantes.hpp"

class Terreno;
class Explosao;
class Projetil;

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

    /* Propriedades Físicas do Cenário */
    static constexpr double GRAVIDADE           = 50.0;


    /* Objetos no cenário */
    //std::set<int, CenarioObject *> objetos;
    Terreno *terreno;                           // Terreno atual
    std::vector<Tanque> tanques;                // Lista de tanques no cenário, na ordem da esquerda para a direita
    Projetil *projetil;                         // Projétil em voo
    Explosao *explosao;                         // Explosão atualmente ocorrendo

    int vento;                                  // Vento no cenário atual. + para dir.
    int      n_jogadores_vivos;                 // Guarda o número de jogadores vivos.

    bool controle_jogador;                      // Estado do cenário: true = não responde ao jogador; true = jogador no controle.
    std::vector<Tanque>::iterator tanqueNaVez;  // De quem é a vez. É um iterador, pois permite determinar o próximo jogador usando o operador ++.
    Tanque *tanqueEmFoco;                       // Tanque cujo nome de jogador aparecerá no topo da tela. É um ponteiro, pois é mais fácil referenciá-lo desta forma.
    Tanque *tanqueMorrendo;                     // Armazena o jogador cuja animação de morte está atualmente sendo executada.
    std::queue<Tanque *> filaTanquesMortos;     // Armazena uma referência ao tanque (ponteiro).


public:
    explicit Cenario(const std::vector<Jogador *> &listaJogadores);
    ~Cenario();

    // getters
    int getVento() const;
    int getGravidade() const;
    double getCoordenadaZ(double x, double y);      // Retorna a coordenada z do solo em (x, y)

    // Verificar se a posição do projétil atinge algum obstáculo no cenário
    bool ocorreuColisaoEntreProjetilEObstaculo();
private:
    bool atingiuTerreno();
    bool atingiuUmTanque();

public:
    // Gerenciar teclas para controlar os tanques
    void gerenciar_teclado(unsigned char);
    void gerenciar_teclas_especiais(int);

    // Exibe o cenário na tela
    void exibir();                      // Exibe o cenário atual na tela


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
    void posicionar_camera();
    int  definir_vento();               // Define vento conforme configurações do jogo
    void criarListaDeTanquesEmOrdemAleatoria(std::vector<Jogador *> const &listaJogadores);  // Cria os tanques do cenário a partir da lista de juogadores recebida
    void posicionarTanques();           // Posiciona os tanques no cenário, após eles terem sido reordenados.

    void desenhar();                    // Desenha o cenário em si: terreno, jogadores, projéteis, explosões, etc.
    void desenhar_na_viewport2D();      // Configura VP 2D e desenha informações
    void desenhar_na_viewport3D();      // Configura VP 3D e desenha cenário

    void registrarDanoAosTanquesAfetados();
    void registrarVitoriaAosTanquesSobreviventes() const;

    /* Função auxiliar - seleciona um elemento aleatório de um container C++ que possui iterador */
    static std::default_random_engine gerador;

    template<typename iteratorType>
    static iteratorType selecionarElementoAleatorio(iteratorType first, iteratorType last);     // Seleciona um tanque aleatório da lista de tanques

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
// constexpr GLfloat Cenario::SOMBRA[];
//
// Isso foi feito no arquivo .cpp.

#endif
