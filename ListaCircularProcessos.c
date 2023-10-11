#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Processo{
char nome[30];
int prioridade;
float taxaCompleto;
float taxaPorCiclo;
int tempoProcessamento;
struct Processo *prox;
}Processo;

void insereprocesso(Processo** inicio){

    Processo *novo_proc = (Processo*) malloc(sizeof(Processo));
    
    printf("Digite o nome do processo: ");
    fgets(novo_proc->nome, 30, stdin);
    getchar();
    printf("Entre com sua prioridade: ");
    scanf("%d", &novo_proc->prioridade);
    fflush(stdin);
    getchar();
    printf("Entre com sua taxa por ciclo: ");
    scanf("%f", &novo_proc->taxaPorCiclo);
    printf("Entre com o tempo de processamento: ");
    scanf("%d", &novo_proc->tempoProcessamento);
    printf("\n\n");
    novo_proc->prox = NULL;

    if(*inicio == NULL){

    *inicio = novo_proc;
    novo_proc->prox = *inicio;
    
    return;
    }
    
    Processo *aux = *inicio;
    
    if(aux->prioridade > novo_proc->prioridade){
    
    novo_proc->prox = *inicio;
    
    while(aux->prox != *inicio){
        aux = aux->prox;
    }

    aux->prox = novo_proc;
    *inicio = novo_proc;
    
    return;
    }
    
    while(aux->prox != *inicio && aux->prox->prioridade < novo_proc->prioridade){
        aux = aux->prox;
    }
    
    novo_proc->prox = aux->prox;
    aux->prox = novo_proc;
}

void iniciarlista(Processo** inicio){
    printf("a");
    return;
}


int main(){

    Processo* inicio = NULL;
    int numprocessos = 0;

    printf("Quantos processos serão adicionados? (máx 5)\n");
    scanf("%d", &numprocessos);

    for(int i = 0; i < numprocessos; i++){
        insereprocesso(&inicio);
        printf("\n");
    }
    
    iniciarlista(&inicio);

    return 0;
}