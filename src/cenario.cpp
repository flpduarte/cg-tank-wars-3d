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

// desativar asserts qdo programa estiver funcionando
//#define NDEBUG
#include <GL/glut.h>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <graphics/cor.h>
#include "../include/armas.hpp"
#include "../include/jogador.hpp"
#include "../include/terreno.hpp"
#include <cenario.hpp>
#include "../include/globals.hpp"
#include "../include/objetos2D.hpp"
#include "../include/objetos3D.hpp"
#include "../include/explosoes.hpp"
#include "../include/interacoes.hpp"

/* --- Implementação da classe Cenario --- */

// OBSERVAÇÕES SOBRE AS CONSTANTES ESTÁTICAS DA CLASSE:
//
// "Note that the constant initializer is not a definition. You still need to define the static member in an
// enclosing namespace."
// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr038.htm
//
// Resumindo, as expressões em cenario.hpp declaram, mas NÃO INICIAM, as constantes. Para de fato INICIAR
// as constantes (criá-las - para posteriormente receberem o valor definido em cenario.hpp), é preciso
// escrever as linhas abaixo fora da definição da classe:
constexpr GLfloat Cenario::SOMBRA[];
constexpr GLfloat Cenario::POSICAO_SOL[];
constexpr GLfloat Cenario::COR_SOL[];
// Isso porque as demais constantes só serão criadas APÓS A EXECUÇÃO DO CONSTRUTOR (lazy initialization).
// Logo, as linhas acima são obrigatórias para cada constante estática que precise ser iniciada
// antes da execução do construtor  .


/**
 * Cria um novo cenário: Terreno, câmera e ordem de aparecimento dos jogadores.
 */
Cenario::Cenario()
{
    // Cria câmera e terreno
    srand(time(NULL));
    terreno   = new Terreno;

    // Configura cenário
    jogadores           = new Jogador *[mundo.n_jogadores]();
    n_jogadores_vivos   = mundo.n_jogadores;
    projetil            = NULL;
    explosao            = NULL;
    jogador_morrendo    = NULL;
    vento               = definir_vento();                // * a ser implementada
    jog_vez             = rand() % mundo.n_jogadores;
    jog_ativo           = jog_vez;                        // Implementar posteriormene o efeito de queda inicial dos tanques

    // Cria lista aleatória de jogadores
    misturar_jogadores();
    posicionar_jogadores();

    // Configura iluminação do Sol.
    // Obs: Posso futuramente fazer essas configurações mudarem aleatoriamente,
    // para criar cenários noturnos, por exemplo. Mas isto está fora do escopo
    // do trabalho atual.
    glLightfv(GL_LIGHT0, GL_AMBIENT, SOMBRA);           //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, COR_SOL);          //contribuição difusa
    glLightfv(GL_LIGHT0, GL_POSITION, POSICAO_SOL);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Prepara para iniciar vez do jogador atual
    jogadores[jog_vez]->preparar_para_jogar();
    controle_jogador    = true;                    // Jogador já começa ativo
}

/**
 * Destroi cenário após o fim da rodada.
 */
Cenario::~Cenario()
{
    // Desativa efeito de iluminação
    glDisable(GL_LIGHT0);

    // Remove vetores criados
    delete terreno;
    delete jogadores;
    if (projetil != NULL)
    {
        delete projetil;
    }
    if (explosao != NULL)
    {
        delete explosao;
    }
}

/* --- Funções privadas --- */
/**
 * Define um vento aleatório, na faixa de intensidades definida pela configuração
 * do jogo.
 *
 * TODO: implementar esta função posteriormente.
 */
int Cenario::definir_vento()
{
    return 0;
}

/**
 * Mistura a ordem de aparecimento dos jogadores e define suas respectivas
 * posições no cenário.
 */
void Cenario::misturar_jogadores()
{
    // lê jogadores em ordem "aleatória"
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        // Procura um jogador que ainda não existe na lista
        int n;
        do
        {
            n = rand() % mundo.n_jogadores;
        }
        while (existe_elemento(jogadores, i, mundo.jogadores[n]));

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
 * desenhar()
 * Função responsável por desenhar todos os objetos 3D que compõem o cenário.
 */
void Cenario::desenhar()
{
    // Desenha o terreno
    terreno->desenhar();

    // Desenha os jogadores
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        if (jogadores[i]->vivo)
            jogadores[i]->desenhar();
    }

    // Desenha o projétil, se houver
    if (projetil != NULL)
    {
        projetil->desenhar();
    }

    // Desenha a explosão, se houver
    if (explosao != NULL)
    {
        explosao->desenhar();
    }
}


/**
 * Configura a viewport 3D principal e desenha o cenário na viewport.
 */
void Cenario::desenhar_na_viewport3D()
{
    // Configura GL_SCISSOR para coincidir com viewport para limpar a tela com
    // cor azul celeste
    glScissor(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(cor::AZUL_CELESTE[0], cor::AZUL_CELESTE[1], cor::AZUL_CELESTE[2], cor::AZUL_CELESTE[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Ativa iluminação e teste de profundidade
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    // Configura Viewport e Projeção Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, ASPECT_RATIO, DNEAR, DFAR);
    glViewport(VP3D_XMIN, VP3D_YMIN, VP3D_LARGURA, VP3D_ALTURA);

    // Muda para matriz ModelView, posiciona a câmera e desenha o cenário
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    posicionar_camera();
    this->desenhar();
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
    // Limpa a tela para cinza escuro. Assume que Scissor está desligado.
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // define janela de recorte de forma a coincidir
    // coordendas do mundo com coordenadas da janela
    // Nota: Redefinir viewport para ser janela inteira.
    // glLoadIdentity() tem efeito sobre a matriz ativa, mas não faz nada com a viewport!
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, JANELA_LARGURA, 0, JANELA_ALTURA);
    glViewport(0, 0, JANELA_LARGURA, JANELA_ALTURA);   // redefine viewport para ser a janela inteira.

    // Imprime nome do jogador *ativo* no centro da primeira linha
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(JANELA_LARGURA/2, POS_PRIMEIRA_LINHA, 0);
    texto_centralizado(jogadores[jog_ativo]->nome, TAM_TEXTO, FONTE, jogadores[jog_ativo]->cor_real());
    glPopMatrix();

    // 2a linha: angulo à esquerda, Arma à direita
    // Informações são referentes ao jogador da vez atual (nao necessariamente
    // o jogador ativo)
    glPushMatrix();
    glTranslatef(ESPACAMENTO, POS_SEGUNDA_LINHA, 0);
    float larg = desenhar_string("Angulo: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPushMatrix();
    glTranslatef(larg, 0, 0);
    desenhar_string(jogadores[jog_vez]->angulo_texto(), TAM_TEXTO, FONTE, cor::AMARELO);
    glPopMatrix();

    glTranslatef(JANELA_LARGURA - 2*ESPACAMENTO, 0, 0);
    larg = texto_alinhado_direita(jogadores[jog_vez]->lista_armas->arma_atual()->nome, TAM_TEXTO, FONTE, cor::AMARELO);
    glTranslatef(-larg, 0, 0);
    texto_alinhado_direita("Arma: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPopMatrix();

    // 3a Linha: Potencia e Homens
    glPushMatrix();
    glTranslatef(ESPACAMENTO, POS_TERCEIRA_LINHA, 0);
    larg = desenhar_string("Potencia: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPushMatrix();
    glTranslatef(larg, 0, 0);
    desenhar_string(std::to_string(jogadores[jog_vez]->potencia), TAM_TEXTO, FONTE, cor::AMARELO);
    glPopMatrix();

    glTranslatef(JANELA_LARGURA - 2*ESPACAMENTO, 0, 0);
    larg = texto_alinhado_direita(std::to_string(jogadores[jog_vez]->homens), TAM_TEXTO, FONTE, cor::AMARELO);
    glTranslatef(-larg, 0, 0);
    texto_alinhado_direita("Homens: ", TAM_TEXTO, FONTE, cor::LILAS_ESCURO);
    glPopMatrix();
}

/**
 * Funções que respondem ao teclado: teclas comuns e teclas especiais.
 * Nota: durante os eventos de voo do projétil ou outras animações, o
 * estado controle_jogador é falso e o jogo não responderá aos coman-
 * dos do teclado.
 */
void Cenario::gerenciar_teclado(unsigned char tecla)
{
    // Não faz nada se o jogador nao estiver no controle.
    if (!controle_jogador)
        return;

    // Por enquanto a unica tecla a que o jogo responde é o espaço.
    // O restante é via teclas especiais.
    // Implementar outras teclas à medida que o jogo evoluir.
    // Ex: 1, 2, ..., 9, 0: exibe uma janela com informações do
    // jogador selecionado.
    switch (tecla)
    {
        // Espaço: atirar!
        // Cria um projétil no cenário; desativa controle do jogador.
        // Muda estado do cenário para ativar a animação do projétil
        case ' ':
            controle_jogador = false;
            projetil = jogadores[jog_vez]->atirar(vento);
            glutTimerFunc(DT_ANIMACAO, Cenario::animacao_projetil, 1);    // ativa animacao
            break;

            // Tab: muda o armamento
        case '\t':
            jogadores[jog_vez]->lista_armas->selecionar_proxima();
            break;

        default:
            std::cout << "Tecla pressionada: <" << tecla << '>' << '\n';
    }
    glutPostRedisplay();
}


/**
 * Teclas especiais usadas:
 * Setas esquerda e direita: ajustam ângulo
 * Setas para cima e para baixo: ajustam potência
 * Page up/Page down: Aumentam/diminuem a potência de 100 em 100
 */
void Cenario::gerenciar_teclas_especiais(int tecla)
{
    if (!controle_jogador)
        return;

    switch (tecla)
    {
        case GLUT_KEY_LEFT:

            jogadores[jog_vez]->angulo += 1;
            if (jogadores[jog_vez]->angulo > 180)
                jogadores[jog_vez]->angulo = 0;
            break;

        case GLUT_KEY_RIGHT:
            jogadores[jog_vez]->angulo -= 1;
            if (jogadores[jog_vez]->angulo < 0)
                jogadores[jog_vez]->angulo = 180;
            break;

            // Controle de potência. Note o limite pelo número de homens!
        case GLUT_KEY_UP:
        case GLUT_KEY_PAGE_UP:
            jogadores[jog_vez]->potencia += (tecla == GLUT_KEY_PAGE_UP) ? 100 : 1;
            if (jogadores[jog_vez]->potencia > 10*jogadores[jog_vez]->homens)
                jogadores[jog_vez]->potencia = 10*jogadores[jog_vez]->homens;
            break;

        case GLUT_KEY_DOWN:
        case GLUT_KEY_PAGE_DOWN:
            jogadores[jog_vez]->potencia -= (tecla == GLUT_KEY_PAGE_DOWN) ? 100 : 1;
            if (jogadores[jog_vez]->potencia < 0)
                jogadores[jog_vez]->potencia = 0;
            break;
    }
}

/**
 * Funções responsáveis pela animação do projétil.
 * Para ser chamada, assume que this->projetil != NULL.
 */
void Cenario::animacao_projetil(int valor)
{
    mundo.cenario->animar_projetil();
    glutPostRedisplay();
}

void Cenario::animar_projetil()
{
    // atualiza a posição do projétil
    assert(this->projetil != NULL);
    this->projetil->atualizar_posicao();

    // Se projétil atingiu um obstáculo, cria uma explosão no local atual
    if (this->projetil->atingiu_obstaculo())
    {
        this->explosao = this->projetil->detonar();
        delete this->projetil;
        this->projetil = NULL;
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_explosao, 0);   // 0 = explosao projetil
    }

        // Caso contrário, continua a animação do projétil
    else
    {
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_projetil, 1);
    }
}


/**
 * Funções responsáveis pela animação da explosão.
 * Assume que existe explosão ocorrendo no cenário.
 */
void Cenario::animacao_explosao(int value)
{
    mundo.cenario->animar_explosao();
    glutPostRedisplay();
}

void Cenario::animar_explosao()
{
    // Confirma que existe explosão no cenário
    assert(this->explosao != NULL);

    // Chamar esta função continuamente enquanto a animação não tiver terminado.
    if (this->explosao->proximo_frame()) // true enquanto animação não terminar
    {
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_explosao, 0);
    }

        // Caso contrário, analisa os danos causado pela explosão.
    else
    {
        this->analisar_danos();
    }
}


/**
 * analisar_danos()
 * Atualiza o número de homens dos jogadores após a explosão.
 * Apaga o objeto explosao ao final da tarefa.
 *
 * Caso um jogador tenha morrido com a explosão, insere-o em uma
 * fila para executar as animações de morte daquele jogador.
 */
void Cenario::analisar_danos()
{
    // Confirma que existe explosão. Esta função é chamada por animar_explosao().
    assert(this->explosao != NULL);

    // Itera pelos jogadores vivos no cenário e atualiza seus respectivos números
    // de homens.
    for (int i = 0; i < mundo.n_jogadores; i++)
    {
        if (this->jogadores[i]->homens > 0)
        {
            this->jogadores[i]->homens -= this->explosao->dano(this->jogadores[i]->pos);

            // Inclui jogador na fila para executar animação de morte se ele morreu.
            if (this->jogadores[i]->homens <= 0)
            {
                this->jogadores[i]->homens = 0;
                fila_jogadores_mortos.push(i);
            }
        }
    }

    // Apaga o objeto explosão
    delete this->explosao;
    this->explosao = NULL;

    // Voltar para o loop de executar a animação de saída dos jogadores
    retirar_jogadores_mortos();
}

/**
 * Loop que executa a animação de cada jogador que está na fila de
 * jogadores mortos.
 *
 * Após executar cada animação, muda a flag "vivo" para false do jogador,
 * a fim de que ele não seja mais exibido no cenário.
 *
 * Quando não houver mais jogadores com homens = 0 para executar animação,
 * a função verifica se há mais de 1 jogador no cenário.
 *
 * Se houver, devolve o controle para o próximo jogador da vez.
 * Caso contrário, dá a vitória ao jogador vivo e encerra o cenário.
 */
void Cenario::retirar_jogadores_mortos()
{
    // Executa animações de morte.
    if (!fila_jogadores_mortos.empty())
    {
        // retira índice do jogador da fila e o salva na variável jogador_morrendo
        int i_jogador    = fila_jogadores_mortos.front();
        jogador_morrendo = jogadores[i_jogador];
        n_jogadores_vivos--;                                // menos 1 jogador vivo
        jog_ativo        = i_jogador;                       // Mostra na tela o nome do jogador que morreu

        fila_jogadores_mortos.pop();
        glutTimerFunc(DT_ANIMACAO, Cenario::animacao_morte_jogador, 1);
    }

        // Se não houver mais jogadores na fila, verificar se encerra o jogo ou se
        // muda a vez para o próximo jogador.
    else
    {
        jogador_morrendo = NULL;
        if (this->rodada_encerrou())
        {
            // dá um pequeno intervalo entre a ultima animação e ir para o
            // resultado parcial.
            glutTimerFunc(500, resultado_parcial, 0);
        }

            // Iniciar a vez do próximo jogador
        else
        {
            iniciar_vez_do_proximo_jogador();
        }
    }
}


/**
 * rodada_encerrou()
 * Verifica número de jogadores vivos.
 * - 2 ou mais jogadores vivos: retorna false.
 * - 1 jogador vivo: incrementa o número de vitórias desse jogador.
 *   Retorna true.
 * - 0 jogadores vivos: retorna true.
 */
bool Cenario::rodada_encerrou()
{
    bool resultado;

    // 0 ou 1 jogador - rodada encerrou.
    if (this->n_jogadores_vivos < 2)
    {
        if (this->n_jogadores_vivos == 1)
        {
            Jogador **j = jogadores;
            while (!(*j)->vivo)
            {
                j++;
            }
            (*j)->vitorias++;
        }
        resultado = true;
    }

        // Mais de 1 jogador: retorna false
    else
    {
        resultado = false;
    }

    return resultado;
}

/**
 * Inicia a vez do próximo jogador.
 * Assume que há pelo menos 2 jogadores vivos!
 */
void Cenario::iniciar_vez_do_proximo_jogador()
{
    assert (n_jogadores_vivos > 1);
    do
    {
        jog_vez = (jog_vez + 1) % mundo.n_jogadores;
    }
    while (!jogadores[jog_vez]->vivo);

    // Faz jogador da vez tmb ser o jogador ativo e segue o jogo!
    jog_ativo = jog_vez;
    jogadores[jog_vez]->preparar_para_jogar();
    controle_jogador = true;
}

/**
 * Funções responsáveis pela animação da morte de um jogador.
 * Manipula a variável jogador_morrendo.
 */
void Cenario::animacao_morte_jogador(int value)
{
    mundo.cenario->animar_morte_jogador();
    glutPostRedisplay();
}

void Cenario::animar_morte_jogador()
{
    jogador_morrendo->morte_proximo_frame();

    // Se ainda não tiver acabado os frames de animação, usar glutTimerFunc para
    // continuar animando
    if (!jogador_morrendo->anim_finalizada)
    {
        glutTimerFunc(DT_ANIMACAO, animacao_morte_jogador, 1);
    }

        // Acabou animação: remove jogador morrendo da tela
    else
    {
        jogador_morrendo->vivo = false;
        jogador_morrendo = NULL;

        // Anima uma eventual explosao que a animação possa ter criado.
        if (explosao != NULL)
        {
            glutTimerFunc(DT_ANIMACAO, animacao_explosao, 0);
        }

            // Senão, volta para retirar_jogadores_mortos()
        else
        {
            retirar_jogadores_mortos();
        }
    }
}

/**
 * Utilizada pela animação da morte de jogadores, esta função cria uma explosão
 * no local indicado pelo cenário.
 *
 * Futuramente, esta função pode ser implementada como uma "fila de explosões".
 */
void Cenario::criar_explosao(double pos[3], double raio)
{
    assert (explosao == NULL);
    explosao = new Explosao(pos, raio);
}

/**
 * z_solo(): Retorna a posição z do solo na posição (x, y) dada.
 */
double Cenario::z_solo(double x, double y)
{
    return this->terreno->z(x, y);
}

void Cenario::posicionar_camera()
{
    gluLookAt(CAMERA_POS[0], CAMERA_POS[1], CAMERA_POS[2],
              CAMERA_LOOKAT[0], CAMERA_LOOKAT[1], CAMERA_LOOKAT[2],
              CAMERA_VIEWUP[0], CAMERA_VIEWUP[1], CAMERA_VIEWUP[2]);
}

