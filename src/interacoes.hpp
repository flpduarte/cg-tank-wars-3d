/**
 * interacoes.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Define as funções necessárias pelo OpenGL para realizar:
 * - Interações com Teclado - teclas normais e especiais
 * - Interação com o Mouse (se houver)
 * - Função principal de exibição
 * - Função de animação, se necessária.
 *
 * Além disso, também define as funções de mudança de tela, para serem passadas
 * como ação aos botões do menu. Como no caso das interações do OpenGL, essas
 * funções devem ser estáticas, e apenas servirão para chamar o método corres-
 * pondente do objeto Mundo.
 */
#ifndef INTERACOES_HPP
#define INTERACOES_HPP

void interacao_teclado(unsigned char, int, int);
void interacao_teclas_especiais(int, int, int);
void interacao_mouse(int, int, int, int);
void funcao_exibicao();

void tela_inicial();            // Vai para a tela inicial
void renomear_jogadores();      // Tela inicial -> Escolha jogadores
void iniciar_jogo();            // Escolha jogadores -> jogo
void iniciar_rodada();          // Inicia o loop de uma rodada_atual
void resultado_parcial();       // Vai para TELA_RESULTADO_PARCIAL e exibe placares.
void tela_compras(unsigned int);// Exibe o menu de compras de cada jogador

#endif
