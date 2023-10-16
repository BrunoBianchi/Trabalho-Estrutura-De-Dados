#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int lengthProcesso = 0;
typedef struct Processo
{
    char nome[30];
    int prioridade;
    float taxaCompleto;
    float taxaPorCiclo;
    int tempoProcessamento;
    struct Processo *prox;
} Processo;

void adicionarProcesso(Processo **inicio);
void comecarProcessamento(Processo **inicio);
void excluirProcessamento(Processo **inicio, char nome[]);
int main()
{
    Processo *proc = NULL;
    for (int i = 0; i < 5; i++)
    {
        adicionarProcesso(&proc);
    }
    comecarProcessamento(&proc);
    return 0;
}

void adicionarProcesso(Processo **inicio)
{
    if (lengthProcesso >= 5)
    {
        printf("Sistema ja esta cheio!\n");
        return;
    }
    Processo *novo_proc = (Processo *)malloc(sizeof(Processo));
    char nome[30];
    printf("Digite o nome do processo: ");
    fflush(stdin);
    scanf("%s", &nome);
    nome[strlen(nome) + 1] = '\0';
    strcpy(novo_proc->nome, nome);
    printf("Prioridade do processo (1 a 5): ");
    scanf("%d", &novo_proc->prioridade);
    printf("Digite a taxa por ciclo do processo: ");
    scanf("%f", &novo_proc->taxaPorCiclo);
    printf("Digite o tempo de processamento do processo: ");
    scanf("%d", &novo_proc->tempoProcessamento);
    novo_proc->taxaCompleto = 0;
    if (*inicio == NULL)
    {
        *inicio = novo_proc;
        novo_proc->prox = *inicio;
        lengthProcesso++;
        puts("\n");
        return;
    }
    else
    {

        Processo *aux = *inicio;

        while (aux)
        {
            // Verificar se ja existe algum processo com prioridade
            if (aux->prioridade == novo_proc->prioridade)
            {
                printf("\nJa existe um processo com essa prioridade!\n");
                return;
            }
            // Insercao no inicio
            if (novo_proc->prioridade < aux->prioridade && aux == *inicio)
            {
                novo_proc->prox = aux;
                aux->prox = novo_proc;
                *inicio = novo_proc;
                lengthProcesso++;
                puts("\n");
                return;
                // Insercao no meio
            }
            else if (novo_proc->prioridade > aux->prioridade && novo_proc->prioridade < aux->prox->prioridade)
            {
                novo_proc->prox = aux->prox;
                aux->prox = novo_proc;
                lengthProcesso++;
                puts("\n");
                return;
                // Insercao no fim
            }
            else if (novo_proc->prioridade > aux->prioridade && aux->prox == *inicio)
            {
                aux->prox = novo_proc;
                novo_proc->prox = *inicio;
                lengthProcesso++;
                puts("\n");
                return;
            }
            aux = aux->prox;
        }
    }
}
void excluirProcessamento(Processo **inicio, char nome[])
{
    Processo *aux = *inicio;
    while (aux)
    {
        // Remocao no Inicio
        if (strcmp(nome, aux->nome) == 0 && aux == *inicio)
        {
            Processo *aux2 = aux;
            *inicio = aux->prox;
            printf("%s Finalizado!\n\n", &aux2->nome);
            lengthProcesso--;
            return;
            // Remocao do meio
        }
        else if (strcmp(nome, aux->prox->nome) == 0 && aux->prox->prioridade > aux->prioridade && aux->prox->prioridade < aux->prox->prox->prioridade)
        {
            Processo *aux2 = aux->prox;
            aux->prox = aux->prox->prox;
            printf("%s Finalizado!\n\n", &aux2->nome);
            lengthProcesso--;
            return;
        }
        else if (strcmp(nome, aux->prox->nome) == 0 && aux->prox->prioridade > aux->prioridade && aux->prox->prox == *inicio)
        {
            Processo *aux2 = aux->prox;
            aux->prox = *inicio;
            printf("%s Finalizado!\n\n", &aux2->nome);
            lengthProcesso--;
            return;
        }
        aux = aux->prox;
    }
    return;
}

void comecarProcessamento(Processo **inicio)
{
    Processo *aux = *inicio;
    while (aux)
    {
        printf("%s entrou no processador\n\n", aux->nome);
        aux->taxaCompleto += aux->taxaPorCiclo;
        Sleep(aux->tempoProcessamento * 1000);
        if (aux->taxaCompleto >= 100)
        {
            printf("%s saiu do processador com uma taxa de 100 %% \n\n", aux->nome, aux->taxaCompleto);
        }
        else
        {
            printf("%s saiu do processador com uma taxa de %.1f %% \n\n", aux->nome, aux->taxaCompleto);
        }

        if (aux->taxaCompleto >= 100)
        {
            excluirProcessamento(&(*inicio), aux->nome);
            free(aux);
        }
        if (lengthProcesso <= 0)
            break;
        aux = aux->prox;
    }
    printf("Todos os processos foram finalizdos!\n\n");
}