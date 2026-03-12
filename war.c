#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

// estrutura do território
typedef struct {
    char nome[50];
    char exercito[20];
    int tropas;
} Territorio;

// tipos de missão possíveis
typedef enum {
    DESTRUIR_VERDE,
    CONQUISTAR_3
} TipoMissao;

// estrutura da missão
typedef struct {
    TipoMissao tipo;
    int concluida;
} Missao;


// funções
void iniciarMapa(Territorio *mapa);
void gerarMissao(Missao *m);
void mostrarMapa(Territorio *mapa);
void atacar(Territorio *a, Territorio *d);
int checarMissao(Missao *m, Territorio *mapa);


int main() {

    srand(time(NULL));

    // alocação dinâmica do mapa
    Territorio *mapa = calloc(TOTAL_TERRITORIOS, sizeof(Territorio));

    if(mapa == NULL){
        printf("Erro de memoria\n");
        return 1;
    }

    Missao minhaMissao;

    iniciarMapa(mapa);
    gerarMissao(&minhaMissao);

    int op = -1;

    while(op != 0){

        mostrarMapa(mapa);

        printf("\n====== MENU ======\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar missão\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d",&op);

        if(op == 1){

            int atk, def;

            printf("Territorio atacante (1-5): ");
            scanf("%d",&atk);

            printf("Territorio defensor (1-5): ");
            scanf("%d",&def);

            if(atk >=1 && atk <=5 && def >=1 && def <=5 && atk != def){

                atacar(&mapa[atk-1], &mapa[def-1]);

            }else{
                printf("IDs invalidos\n");
            }
        }

        else if(op == 2){

            if(checarMissao(&minhaMissao, mapa)){

                printf("\n=====================\n");
                printf("MISSAO CONCLUIDA!\n");
                printf("=====================\n");

                op = 0;

            }else{
                printf("\nMissao ainda nao concluida\n");
            }
        }
    }

    free(mapa);

    return 0;
}



// inicia os territórios
void iniciarMapa(Territorio *mapa){

    char *nomes[] = {"Brasil","Egito","China","Russia","Canada"};
    char *cores[] = {"Verde","Azul","Verde","Vermelho","Azul"};

    for(int i=0;i<TOTAL_TERRITORIOS;i++){

        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].exercito, cores[i]);

        mapa[i].tropas = (rand()%5)+3; // entre 3 e 7 tropas
    }
}


// sorteia missão
void gerarMissao(Missao *m){

    m->tipo = rand()%2;
    m->concluida = 0;

    printf("\nSUA MISSAO: ");

    if(m->tipo == DESTRUIR_VERDE){
        printf("Destruir o exercito Verde\n");
    }else{
        printf("Conquistar 3 territorios\n");
    }

}


// mostra o mapa
void mostrarMapa(Territorio *mapa){

    printf("\n-------------------------------------\n");
    printf("ID | Territorio | Exercito | Tropas\n");
    printf("-------------------------------------\n");

    for(int i=0;i<TOTAL_TERRITORIOS;i++){

        printf("%d | %s | %s | %d\n",
               i+1,
               mapa[i].nome,
               mapa[i].exercito,
               mapa[i].tropas);
    }
}


// sistema de ataque simples
void atacar(Territorio *a, Territorio *d){

    if(a->tropas <= 1){
        printf("Esse territorio nao pode atacar\n");
        return;
    }

    int dadoAtk = (rand()%6)+1;
    int dadoDef = (rand()%6)+1;

    printf("Ataque %d vs Defesa %d\n",dadoAtk,dadoDef);

    if(dadoAtk >= dadoDef){

        d->tropas--;

        if(d->tropas <= 0){

            printf("Territorio conquistado!\n");

            strcpy(d->exercito, a->exercito);

            d->tropas = 1;
            a->tropas--;
        }

    }else{

        a->tropas--;

        printf("Ataque falhou\n");
    }
}


// verifica se missão foi cumprida
int checarMissao(Missao *m, Territorio *mapa){

    if(m->tipo == DESTRUIR_VERDE){

        for(int i=0;i<TOTAL_TERRITORIOS;i++){

            if(strcmp(mapa[i].exercito,"Verde")==0){
                return 0;
            }
        }

        return 1;
    }

    else{

        int cont = 0;

        for(int i=0;i<TOTAL_TERRITORIOS;i++){

            if(strcmp(mapa[i].exercito,"Azul")==0){
                cont++;
            }
        }

        if(cont >= 3)
            return 1;
        else
            return 0;
    }
}