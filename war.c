// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

  //  return 0;


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Funções auxiliares ---

// Cadastro dos territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do Território %d\n", i + 1);
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibir todos os territórios
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== Mapa dos Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[!] Ataque inválido: ambos têm a mesma cor!\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("\n[!] Tropas insuficientes para atacar.\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n>>> Batalha: %s (atacante) vs %s (defensor)\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu!\n");
        atacante->tropas -= 1;
    }
}

// Função para sortear e atribuir uma missão ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibir a missão de um jogador (somente no início)
void exibirMissao(char* missao, int jogador) {
    printf("\n=== Missão do Jogador %d ===\n", jogador);
    printf("%s\n", missao);
    printf("----------------------------\n");
}

// Verificar se uma missão foi cumprida (lógica simples inicial)
int verificarMissao(char* missao, Territorio* mapa, int n) {
    if (strstr(missao, "Conquistar 3")) {
        int contador = 0;
        char corRef[10];
        strcpy(corRef, mapa[0].cor);

        // Conta quantos territórios seguidos da mesma cor
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, corRef) == 0)
                contador++;
            else
                contador = 1; // reinicia a contagem

            if (contador >= 3)
                return 1;
        }
    }
    else if (strstr(missao, "Eliminar vermelha")) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                return 0;
        }
        return 1;
    }
    else if (strstr(missao, "Dominar todos")) {
        char corRef[10];
        strcpy(corRef, mapa[0].cor);
        for (int i = 1; i < n; i++) {
            if (strcmp(mapa[i].cor, corRef) != 0)
                return 0;
        }
        return 1;
    }
    // Outras missões podem ser expandidas
    return 0;
}

// Liberação de memória
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int numJogadores) {
    free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

// --- Função principal ---
int main() {
    srand(time(NULL));

    int n, numJogadores;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Aloca os territórios dinamicamente
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);

    printf("\nDigite o número de jogadores: ");
    scanf("%d", &numJogadores);

    // Lista de missões disponíveis
    char* missoesDisponiveis[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar todos os territórios do mapa",
        "Manter pelo menos 2 territórios com mais de 10 tropas",
        "Possuir territórios de cores diferentes"
    };
    int totalMissoes = 5;

    // Alocação dinâmica para as missões de cada jogador
    char** missoesJogadores = (char**) malloc(numJogadores * sizeof(char*));
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoesDisponiveis, totalMissoes);
        exibirMissao(missoesJogadores[i], i + 1);
    }

    // Loop principal do jogo
    int op;
    int vencedor = -1;
    do {
        printf("\n=== Menu de Ações ===\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Exibir territórios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            int iAtacante, iDefensor;
            printf("Digite o território atacante (1 a %d): ", n);
            scanf("%d", &iAtacante);
            printf("Digite o território defensor (1 a %d): ", n);
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > n || iDefensor < 1 || iDefensor > n) {
                printf("[!] Índice inválido!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
                exibirMapa(mapa, n);
            }

            // Verifica silenciosamente se algum jogador cumpriu sua missão
            for (int j = 0; j < numJogadores; j++) {
                if (verificarMissao(missoesJogadores[j], mapa, n)) {
                    vencedor = j + 1;
                    break;
                }
            }
        } else if (op == 2) {
            exibirMapa(mapa, n);
        }

    } while (op != 0 && vencedor == -1);

    if (vencedor != -1) {
        printf("\n🎉 O Jogador %d cumpriu sua missão e venceu o jogo! 🎉\n", vencedor);
    }

    liberarMemoria(mapa, missoesJogadores, numJogadores);
    printf("\nPrograma encerrado.\n");
    return 0;
}


