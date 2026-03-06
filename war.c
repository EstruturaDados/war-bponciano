#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

// Estruturas de Dados
typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

typedef enum { DESTRUIR_VERDE, CONQUISTAR_3 } TipoMissao;

typedef struct {
    TipoMissao tipo;
    int concluida;
} Missao;

// --- Protótipos das Funções (Modularização) ---
void inicializarMapa(Territorio *mapa);
void sortearMissao(Missao *m);
void exibirMapa(const Territorio *mapa); // const: garante que a função não altere o mapa
void realizarAtaque(Territorio *ataca, Territorio *defende);
int verificarMissao(const Missao *m, const Territorio *mapa);
void limparBuffer();

int main() {
    srand(time(NULL));
    
    // Alocação Dinâmica
    Territorio *mapa = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    Missao minhaMissao;

    if (!mapa) return 1;

    inicializarMapa(mapa);
    sortearMissao(&minhaMissao);

    int opcao = -1;
    while (opcao != 0) {
        exibirMapa(mapa);
        printf("\n--- MENU MESTRE ---\n");
        printf("1. Atacar\n");
        printf("2. Verificar Missao\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;
            printf("ID Atacante (1-5): "); scanf("%d", &a);
            printf("ID Defensor (1-5): "); scanf("%d", &d);
            
            if (a >= 1 && a <= 5 && d >= 1 && d <= 5 && a != d) {
                realizarAtaque(&mapa[a-1], &mapa[d-1]);
            }
        } 
        else if (opcao == 2) {
            if (verificarMissao(&minhaMissao, mapa)) {
                printf("\n==================================\n");
                printf("  PARABENS! MISSAO CUMPRIDA!  \n");
                printf("==================================\n");
                opcao = 0; // Finaliza o jogo após vitória
            } else {
                printf("\n[STATUS] Missao ainda em andamento. Continue lutando!\n");
            }
        }
    }

    free(mapa);
    return 0;
}

// --- Implementação dos Módulos ---

void inicializarMapa(Territorio *mapa) {
    char *nomes[] = {"Brasil", "Egito", "China", "Russia", "Canada"};
    char *cores[] = {"Verde", "Azul", "Verde", "Vermelho", "Azul"};
    
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].numeroTropas = (rand() % 5) + 3; // Inicializa com 3 a 7 tropas
    }
}

void sortearMissao(Missao *m) {
    m->tipo = rand() % 2;
    m->concluida = 0;
    printf("\n>>> SUA MISSAO: %s\n", 
           (m->tipo == DESTRUIR_VERDE) ? "Destruir o exercito Verde!" : "Conquistar 3 territorios!");
}

void exibirMapa(const Territorio *mapa) {
    printf("\n%-3s | %-15s | %-12s | %-6s\n", "ID", "TERRITORIO", "EXERCITO", "TROPAS");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%-3d | %-15s | %-12s | %-6d\n", i+1, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
    }
}

void realizarAtaque(Territorio *ataca, Territorio *defende) {
    if (ataca->numeroTropas <= 1) return;

    int dAtk = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;

    if (dAtk >= dDef) {
        defende->numeroTropas--;
        if (defende->numeroTropas <= 0) {
            strcpy(defende->corExercito, ataca->corExercito);
            defende->numeroTropas = 1;
            ataca->numeroTropas--;
        }
    } else {
        ataca->numeroTropas--;
    }
}

int verificarMissao(const Missao *m, const Territorio *mapa) {
    if (m->tipo == DESTRUIR_VERDE) {
        for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0) return 0;
        }
        return 1;
    } else {
        // Exemplo simplificado: Jogador é o exército "Azul" (ID 2 inicial)
        int contagem = 0;
        for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, "Azul") == 0) contagem++;
        }
        return (contagem >= 3);
    }
}

void limparBuffer() {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}