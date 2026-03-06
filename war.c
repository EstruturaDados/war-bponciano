#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

// Estrutura base do território
typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para realizar o ataque entre dois territórios usando ponteiros
void realizarAtaque(Territorio *ataca, Territorio *defende) {
    if (ataca->numeroTropas <= 1) {
        printf("\n[AVISO] O territorio %s nao tem tropas suficientes para atacar (minimo 2).\n", ataca->nome);
        return;
    }

    // Sorteio dos dados (1 a 6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s vs %s ---\n", ataca->nome, defende->nome);
    printf("Dado Ataque [%s]: %d\n", ataca->nome, dadoAtaque);
    printf("Dado Defesa [%s]: %d\n", defende->nome, dadoDefesa);

    // Lógica: Empate ou vitória do atacante favorece o ataque nesta regra
    if (dadoAtaque >= dadoDefesa) {
        printf("VITORIA DO ATACANTE! %s perdeu 1 tropa.\n", defende->nome);
        defende->numeroTropas--;

        // Regra de conquista
        if (defende->numeroTropas <= 0) {
            printf("!!! TERRITORIO CONQUISTADO !!!\n");
            printf("%s agora pertence ao exercito %s.\n", defende->nome, ataca->corExercito);
            strcpy(defende->corExercito, ataca->corExercito);
            defende->numeroTropas = 1; // Ocupação inicial
            ataca->numeroTropas--;    // Tropa que se moveu para ocupar
        }
    } else {
        printf("DEFESA VENCEU! %s perdeu 1 tropa.\n", ataca->nome);
        ataca->numeroTropas--;
    }
}

void exibirMapa(Territorio *mapa) {
    printf("\n%-3s | %-18s | %-12s | %-6s\n", "ID", "TERRITORIO", "EXERCITO", "TROPAS");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%-3d | %-18s | %-12s | %-6d\n", 
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
    }
}

int main() {
    srand(time(NULL)); // Semente para números aleatórios

    // ALOCAÇÃO DINÂMICA: calloc aloca e zera a memória
    Territorio *mapa = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Cadastro inicial
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do Exercito: ");
        fgets(mapa[i].corExercito, 20, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].numeroTropas);
        limparBuffer();
        printf("\n");
    }

    int op = -1;
    while (op != 0) {
        exibirMapa(mapa);
        printf("\nMENU DE GUERRA:\n1 - Iniciar Ataque\n0 - Sair\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            int idAtacante, idDefensor;
            printf("ID do Atacante (1-5): ");
            scanf("%d", &idAtacante);
            printf("ID do Defensor (1-5): ");
            scanf("%d", &idDefensor);

            if (idAtacante >= 1 && idAtacante <= 5 && idDefensor >= 1 && idDefensor <= 5 && idAtacante != idDefensor) {
                // Passamos os endereços dos territórios para a função de ataque
                realizarAtaque(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
            } else {
                printf("\n[ERRO] IDs invalidos ou ataque ao mesmo territorio!\n");
            }
        }
    }

    // LIBERAÇÃO DE MEMÓRIA: Essencial após o uso de calloc
    free(mapa);
    printf("\nMemoria liberada. Ate a proxima batalha!\n");

    return 0;
}