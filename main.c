#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_MIN 12
int verifica_termino(int* duracao, int len);
int posicao_do_menor_processo(int* duracao, int* criacao ,int len ,int tempo_atual);
int main (void) {
    printf("************Trabalho N2 - ECOS01 - SPN (Shortest Proccess Next)************");
    printf("\n");
    printf("\n");
    FILE *entrada;
    entrada = fopen ("entrada.txt", "r");
    if (entrada == NULL) {
        printf ("\nNão encontrei o arquivo!\n");
        exit (EXIT_FAILURE);
    }
    int count =1;
    int criacao[NUM_MIN];
    int duracao[NUM_MIN];
    int prioridade[NUM_MIN];
    int indice =0;
    while (indice<NUM_MIN) {
        int x;
        int k = fscanf (entrada, "%d", &x);
        if (k != 1) break;
        if(count ==1){
            criacao[indice] = x;
            count++;
        }
        else if(count ==2){
            duracao[indice] = x;
            count++;
        }
        else if (count ==3){
            prioridade[indice] = x;
            count++;
            count =1;
            indice++;
        }
    }
    fclose (entrada);
    int i=0;
    for( i = 0; i < NUM_MIN; i++){
        printf("Processo %d - T_Criacao: %d - T_Duracao: %d - Prioridade: %d", i+1,criacao[i],duracao[i],prioridade[i]);
        printf("\n");
    }

    printf("\n");
    printf("\n");
    printf("Inciando escalonamento...\n\n");
    int tempo =0;
    printf("tempo  ");
    for(i=0; i<10; i++){
        printf("  P%d",i+1);
    }
    for(i=10; i<NUM_MIN; i++){
        printf(" P%d",i+1);
    }
    printf("\n");

    int indice_impressao = 0;
    float tempo_medio_de_vida = 0;
    float tempo_medio_de_espera = 0;
    int troca_de_contextos = NUM_MIN;
    int processo_atual =NUM_MIN+1; /*comparar com o maior numero de processo +1*/
    for(i=0; i<NUM_MIN; i++){
        tempo_medio_de_vida = tempo_medio_de_vida + duracao[i];
    }
    while(verifica_termino(duracao, NUM_MIN) == -1){
        int posicao =posicao_do_menor_processo(duracao, criacao, NUM_MIN, tempo);
        duracao[posicao]--;
        if(processo_atual!= posicao){/*verifica chegada de novo processo*/
            processo_atual = posicao;
            tempo_medio_de_espera += (tempo - criacao[posicao]);
        }

        if(tempo<9){
            printf("%d - %d    ", tempo,tempo+1);
        }else{
            if(tempo<10){
                printf("%d - %d   ", tempo,tempo+1);
            }else{
                printf("%d - %d  ", tempo,tempo+1);
            }
        }

        for(indice_impressao=0; indice_impressao<posicao; indice_impressao++){
            printf("--  ");
        }
        printf("##  ");
        for(indice_impressao=0; indice_impressao<NUM_MIN -posicao-1; indice_impressao++){
            printf("--  ");
        }
        printf("\n");
        /*printf("Processo %d sendo realizado ...\n", posicao +1);*/
        tempo++;
        processo_atual = posicao;

    }
    printf("\n");
    printf("Tempo total %d\n", tempo);
    printf("Troca de contextos %d\n", NUM_MIN);
    tempo_medio_de_espera = tempo_medio_de_espera/NUM_MIN;
    tempo_medio_de_vida = tempo_medio_de_vida/NUM_MIN;
    printf("Tempo medio de vida %.2f\n", tempo_medio_de_vida);
    printf("Tempo medio de vida %.2f\n", tempo_medio_de_espera);
    return EXIT_SUCCESS;
}

int verifica_termino(int* duracao, int len){
    int i =0;
    for(i=0; i< len; i++){
        if(duracao[i] > 0){
            return -1; /*retorna -1 enquantto houver processos pendentes*/
        }
    }
    return 1 ;
}

int posicao_do_menor_processo(int* duracao, int* criacao ,int len, int tempo_atual){
    int menor_duracao = 1000000000; int menor_criacao = 1000000000;/*Comparacao com numeros muito altos*/
    int posicao_menor=NUM_MIN+1; /*maior posicao +1*/
    int i =0;
    for(i=0; i< len; i++){
        if(criacao[i] <= tempo_atual){ /*verifica se esta disponivel*/
            if((duracao[i] < menor_duracao)&&(duracao[i]>0)){ /*seleciona a menor duracao sem ser 0*/
                menor_duracao = duracao[i];
            }
        }
    }
    for(i=0; i< len; i++){
        if(duracao[i] == menor_duracao){ /*seleciona entre aqueles que possuem a menor duracao*/
            if((criacao[i] < menor_criacao )&& (criacao[i]<=tempo_atual)){
                menor_criacao = criacao[i];/*seleciona entre os disponiveis o que chegou antes na fila*/
                posicao_menor = i;
            }
        }
    }
    return posicao_menor;
}
