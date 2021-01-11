//
// Created by Felipe on 07/01/2021.
//

#ifndef TANKWARS_TANQUE_H
#define TANKWARS_TANQUE_H

/**
 * Cria uma enumeração para tipos de morte do jogador!
 * Obs: por enquanto, só 1 tipo foi implementado (27/06/18)
 */
enum TipoMorte
{
    MELTDOWN = 0
};

#include <string>
#include <GL/glut.h>
#include <vector>
#include <queue>
#include <globals.hpp>
#include <cenario/CenarioObject.h>

class Projetil;
class Explosao;
class Jogador;

/**
 * Classe Tanque: é responsável pela representação física dos tanques no cenário.
 * Portanto, é esta a classe que armazena as informações de cor atual do tanque, número de homens, bem como do ângulo do
 * canhão e da potência do tiro.
 *
 * A classe Cenário deverá chamar os tanques, e cada tanque por sua vez consulta seu jogador de referência para obter
 * outras informações como qtd de tiros, armas disponíveis e outros.
 *
 * Por fim, é esta a classe que produzirá a animação de morte do tanque.
 * Todo: talvez seja o caso de delegar a morte a outro objeto; analisar essa possibilidade.
 */
class Tanque : public CenarioObject {

    /* Dimensões de referência para desenhar objetos */
public:
    static constexpr double TAMANHO_TANQUE     = 3.0;          // fator de escala do canhão
    static constexpr double HITBOX_TANQUE      = 3.*TAMANHO_TANQUE/4.;
    static constexpr double COMPR_CANHAO       = 0.75;         // comprimento do canhão, sem aplicar fator de escala
    static constexpr double RAIO_CANHAO        = 1/32.;

    static const int POTENCIA_MAXIMA = 1000;
    static constexpr double FATOR_POT_VEL      = 0.16;

private:
    /* Animação do meltdown. TODO: Após implementar a classe Tanque, verificar a possibilidade de delegar a animação de
     * explosão para outra classe. */
    const unsigned int frame_interv_meltdown = 50;

    // Referência ao jogador correspondente a este tanque.
    Jogador &jogador;

    // Posição e cor do tanque
    double posicao[3];      // posição (x, y, z) do tanque
    double vetorNormal[3];   // orientação para cima do tanque. Deve ser unitário.
    float corAtual[4]; // Cor considerando n. de homens. Atualizada pelo método getCorReal(). TODO: talvez esta variável seja desnecessária; confirmar.

    // Estado atual do tanque
    int homens;
    bool vivo;                      // indica se o jogador está vivo ou não, para fins de desenhá-lo no cenário.

    // Estes devem ser alterados via métodos para manter seus valores dentro de seus intervalos válidos.
    int anguloCanhao;               // em graus. Intervalo válido: [0, 180]. 0° = positivo eixo X (direita).
    int potencia;                   // Intervalo válido: [0, 1000].

private:
    // Formas de animação de morte do tanque.
    // A forma de morrer do tanque será definida já no início da rodada!
    int tipo_morte;         // Tipo de morte
    int variacao_morte;     // Variações entre os tipos de morte.
    unsigned int frame;     // número do frame de animação.
    bool animacaoFinalizada;   // indica se a animação finalizou ou não.

public:
    explicit Tanque(Jogador &jogador);

    // getters
    bool isVivo() const;
    const std::string &getNome() const;
    std::string getAnguloEmString() const;          // Retorna o ângulo do tanque em formato de string
    int getPotencia() const;
    int getNumeroDeHomens() const;
    float *getCorReal();                            // Calcula a cor real do tanque baseado no número de homens vivos.
    double *getPosicao();
    bool isAnimacaoFinalizada() const;

    // modificadores do Jogador de referência
    void registrarVitoria() const;

    // Modificadores de ângulo e potência
    void setAnguloPara75Direita();                  // Define o ângulo para 75° para a direita - tanque na extremidade esquerda do terreno
    void setAnguloPara75Esquerda();                 // Define o ângulo para 75° para a esquerda - tanque na extremidade direita do terreno
    void incrementarAnguloSentidoHorario();
    void incrementarAnguloSentidoAntiHorario();
    void aumentarPotenciaLento();                   // Aumenta Potência de 1 em 1
    void aumentarPotenciaRapido();                  // Aumenta Potência de 100 em 100
    void diminuirPotenciaLento();                   // Reduz potência de 1 em 1
    void diminuirPotenciaRapido();                  // Reduz potência de 100 em 100

    // Danos ao tanque
    void removerHomens(int quantidade);             // Reduz os homens do tanque na quantidade especificada.

    // métodos referentes à arma do tanque
    const std::string &getNomeDaArmaAtual() const;
    void selecionarProximaArma() const;


    void desenhar();
    void posicionar(const double nova_pos[3]);    // Posiciona o jogador nas coordenadas dada
    void definir_normal(const GLfloat normal[3]); // Define o sentido "para cima" do tanque

    void preparar_para_jogar();                 // Prepara o jogador para o início da sua vez
    Projetil *atirar(Cenario *cenario) const;     // Cria o projétil correspondente à arma atual
    bool atingiu(const double *X) const;                // Retorna true se a posição do projétil recebida atinge o jogador atual
    void morte_proximo_frame();                 // Executa a animação de morte do jogador atual.
    Explosao *gerarExplosaoAdicional() const;   // Cria a explosão adicional após a execução da animação de morte (se houver).

private:
    void meltdown();

};


#endif //TANKWARS_TANQUE_H
