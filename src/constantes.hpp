/**
 * constantes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Concentra as constantes e tipos enumerados utilizadas no jogo.
 */
#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

/* Constantes gerais */
#define PI 3.14159265358979

/* Constantes da fonte utilizada nos menus */
//#define FONTE            GLUT_STROKE_MONO_ROMAN
#define FONTE            GLUT_STROKE_ROMAN
#define FONTE_ESPESSURA  2
#define FONTE_ALTURA     152.38
#define FONTE_Y0         33.33

/* Configuração padrão do jogo */
#define PADRAO_N_JOGADORES  2
#define PADRAO_N_RODADAS    10
#define MAX_CARACTERES_NOME 15

/* Dimensões e posição da janela */
const int JANELA_LARGURA   =  800;
const int JANELA_ALTURA    =  600;
const int JANELA_POSICAO_X =   50;
const int JANELA_POSICAO_Y =  100;
#define   JANELA_TITULO      "Tank Wars 3D"

/* Dimensões das Viewports durante as rodadas */
const int VP3D_ALTURA      = JANELA_ALTURA - 100;   // 100 pixels p/ informações
const int VP3D_LARGURA     = JANELA_LARGURA;
const int VP3D_XMIN        = 0;
const int VP3D_YMIN        = 0;

/* Dimensões padrão das opções de menu */
#define OPCAOMENU_LARGURA_PADRAO 600
#define OPCAOMENU_ALTURA_PADRAO  50         // inclui borda
#define OPCAOMENU_POSX_PADRAO    0
#define OPCAOMENU_POSY_PADRAO    JANELA_ALTURA - OPCAOMENU_ALTURA_PADRAO
#define OPCAOMENU_LARGURA_BORDA  4

/* Constantes utilizadas por municao.cpp e armas.cpp */
#define MASSA_MUNICAO       1.0   // TBD
#define RAIO_INCINERADOR    5       // Raio de explosão do incinerador; os outros são baseados nesta.
#define QTD_INCINERADOR     100     // Qtd inicial de incineradores por jogador

#define FRACAO_RAIO_DANO    1.25    // Raio de dano / Raio de Explosao no modelo de explosão
#define GRAVIDADE           200.0   // TBD
#define FATOR_POT_VEL       0.01    // Fator que converte potência em velocidade inicial
#define DT                  0.05    // Passo de integração.

/* Dimensões de referência para desenhar objetos */
const double TAMANHO_TANQUE     = 3.0;          // fator de escala do canhão
const double HITBOX_TANQUE      = 3.*TAMANHO_TANQUE/4.;
const double COMPR_CANHAO       = 0.75;         // comprimento do canhão, sem aplicar fator de escala
const double RAIO_CANHAO        = 1/32.;


const float COR_PROJETIL[]       = {0.4, 0.4, 0.4, 1.0};
const float SPECULAR_PROJETIL[]  = {0.75, 0.75, 0.75, 0.75};
const float BRILHO_PROJETIL      = 20.0f;
const float RAIO_PROJETIL        = 1/32. * TAMANHO_TANQUE; // coincide com raio do canhão

/* Constantes utilizadas por mundo.hpp e mundo.c */
const int MAX_JOGADORES     = 10;

/* Definição de algumas cores padrão, em RGBA */
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
    void definir_cor(float *dest, const float *origem);
}


/* Tipos enumerados */
/**
 * Tela: tipo enumerado para definir qual é a tela atual ativa.
 */
enum Tela
{
    TELA_INICIAL,
    TELA_RENOMEAR_JOGADORES,
    TELA_RODADA,
    TELA_RESULTADO_PARCIAL,
    TELA_COMPRAS
};

#endif
