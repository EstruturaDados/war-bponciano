#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

// Definição da planta baixa do dado: a Struct Territorio
typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

// Função para limpar o buffer do teclado (evita bugs com fgets e scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Vetor estático de 5 elementos: o "Mapa" do jogo
    Territorio mapa[TOTAL_TERRITORIOS];

    printf("--- SISTEMA DE ESTRATÉGIA: CADASTRO DE TERRITÓRIOS ---\n\n");

    // Loop para leitura dos dados (Cadastro)
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        printf("Nome do Território: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // Remove o '\n' do final

        printf("Cor do Exército: ");
        fgets(mapa[i].corExercito, 20, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].numeroTropas);
        limparBuffer(); // Limpa o buffer para o próximo fgets não ser ignorado

        printf("---------------------------\n");
    }

    // Exibição do estado atual do mapa
    printf("\n### ESTADO ATUAL DO MAPA ###\n");
    printf("%-20s | %-15s | %-10s\n", "TERRITÓRIO", "COR EXÉRCITO", "TROPAS");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%-20s | %-15s | %-10d\n", 
               mapa[i].nome, 
               mapa[i].corExercito, 
               mapa[i].numeroTropas);
    }

    return 0;
}