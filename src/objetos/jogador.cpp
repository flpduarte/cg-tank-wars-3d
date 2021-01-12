/**
 * jogador.hpp
 *
 * Tank Wars versão 3D
 * Baseado no jogo Tank Wars, por Kenneth Morse
 *
 *
 * Autores:
 * Guilherme Felipe Reis Duarte     RA: 120805
 *
 * Implementa os métodos da classe Jogador.
 *
 */
// para desativar asserts, ativar este comando antes de #define <cassert>
//#define NDEBUG
#include <string>
#include <objetos/jogador.hpp>
#include <objetos/armas/armas.hpp>

void definir_cor(float *, int);     // função local para definir a corBase do tanque

/**
 * Cria um novo jogador.
 * Entrada: número do jogador: 1, 2, ..., MAX_JOGADORES.
 */
Jogador::Jogador(int i)
{
    // define a corBase do tanque:
    definir_cor(this->corBase, i);
    this->nome = "Jogador " + std::to_string(i);
    this->lista_armas = new ListaArmamentos;
}

/**
 * resetar_jogador(): Restaura as configurações do jogador para a condição de
 * início de jogo:
 * - Pontos = 0
 * - Dolares = 0
 * - Armas: Apenas Incinerador, com QTD_INICIAL tiros
 */
void Jogador::resetar_jogador()
{
    // zera pontuação e dolares e reseta lista de armamentos
    this->vitorias = 0;
    this->pontos = 0;
    this->dolares = 0;
    this->lista_armas->condicao_inicial();
}


/**
 * Libera a memória utilizada pelo objeto Jogador
 */
Jogador::~Jogador()
{
    delete lista_armas;
}


/**
 * preparar_para_jogar():
 * Realiza alguns ajustes menores do jogador antes de iniciar a sua vez:
 * - Muda de armamento, caso a munição da arma atual seja = 0;
 * - Muda potência para o máximo possível, caso o jogador tenha
 *   sofrido dano, e a sua última potência selecionada supere a
 *   potência máxima.
 */
void Jogador::preparar_para_jogar()
{
    // Muda arma, se necessário
    if (lista_armas->qtd_atual() <= 0)
    {
        lista_armas->selecionar_proxima();
    }
}

Arma *Jogador::atirarArmaAtual() {
    return lista_armas->atirarArmaAtual();
}


/* -------------------------------------------------------------------------- */
/**
 * Função auxiliar que define a corBase do tanque de acordo com o número do jogador.
 * A definição da corBase segue a mesma sequência que no Tank Wars original.
 * A alteração da corBase é realizada por referência.
 */
void definir_cor(float *cor, const int i)
{
    switch (i)
    {
        case 1:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.;
        break;

        case 2:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 3:
        cor[0] = 0.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 4:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 0.;
        break;

        case 5:
        cor[0] = 0.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 6:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 1.;
        break;

        case 7:
        cor[0] = 1.;
        cor[1] = 1.;
        cor[2] = 1.;
        break;

        case 8:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.;
        break;

        case 9:
        cor[0] = 1.;
        cor[1] = 0.;
        cor[2] = 0.5;
        break;

        case 10:
        cor[0] = 1.;
        cor[1] = 0.5;
        cor[2] = 0.5;
        break;
    }
}
