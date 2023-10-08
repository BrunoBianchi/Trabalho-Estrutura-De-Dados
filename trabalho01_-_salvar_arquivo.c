#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[30];
    int matricula;
    int idade;
    int nroDisciplinas;
    struct Aluno *prox;
} Aluno;

typedef struct Universidade
{
    char nome[30];
    int qtdAlunos;
    struct Universidade *prox;
    struct Aluno *inicioAluno;
} Universidade;

void imprimeU(Universidade *head)
{
    if (head == NULL)
    {
        printf("Lista vazia");
        return;
    }

    Universidade *aux = head;
    while (aux != NULL)
    {
        printf("%s ", aux->nome);
        aux = aux->prox;
    }
}

void imprimeA(Universidade *(head->inicioAluno))
{
    if (head->inicioAluno == NULL)
    {
        printf("Lista vazia");
        return;
    }

    Universidade *aux = head->inicioAluno;
    while (aux->inicioAluno != NULL)
    {
        printf("Nome: %s\n", aux->inicioAluno->nome);
        printf("Matrícula: %d\n", aux->inicioAluno->matricula);
        printf("Idade: %d\n", aux->inicioAluno->idade);
        printf("Quantidade de Matérias: %d\n\n\n", aux->inicioAluno->nroDisciplinas);
        aux->inicioAluno = aux->inicioAluno->prox;
    }
}

void insereU(Universidade **inicio, char nome[], int qtdAlunos)
{
    fflush(stdin);
    printf("Insira uma Universidade: ");
    fgets(nome, 30, stdin);

    Universidade *nova_uni = malloc(sizeof(Universidade));
    strcpy(nova_uni->nome, nome);
    nova_uni->qtdAlunos = qtdAlunos;
    nova_uni->prox = NULL;
    nova_uni->inicioAluno = NULL;

    if (*inicio == NULL)
    {
        *inicio = nova_uni;
        return;
    }
    else{
    Universidade *aux = *inicio;

    while (aux->prox != NULL)
    {
        if (strcmp(nome, aux->nome) == 0)
        {
            printf("Universidade já inserida no sistema!\n");
            break;
        }
        aux = aux->prox;
    }
    
    aux->prox = nova_uni;
    return;
}
}

void InsereA(Universidade **(inicio->inicioAluno), char nome[],){

}

void salvaDados(Universidade *inicio)
{
    FILE *file = fopen("lista_uni.txt", "w");
    if (file == NULL)
    {
        printf("Criando arquivo.\n");
        return;
    }

    Universidade *auxUniv = inicio;
    while (auxUniv != NULL)
    {
        fprintf(file, "%s\n", auxUniv->nome);
        fprintf(file, "%d\n", auxUniv->qtdAlunos);

        Aluno *auxAluno = auxUniv->inicioAluno;
        while (auxAluno != NULL)
        {
            fprintf(file, "%s\n", auxAluno->nome);
            fprintf(file, "%d\n", auxAluno->matricula);
            fprintf(file, "%d\n", auxAluno->idade);
            fprintf(file, "%d\n", auxAluno->nroDisciplinas);
            auxAluno = auxAluno->prox;
        }

        fprintf(file, "\n");
        auxUniv = auxUniv->prox;
    }

    fclose(file);
}

void removerUniversidade(Universidade **inicio)
{
    if (*inicio == NULL)
    {
        printf("Lista Vazia!");
    }
    else
    {
        printf("Digite o nome da universidade:\n");
        char universidadeName[30];
        scanf("%s", &universidadeName);
        universidadeName[strlen(universidadeName) + 1] = '\0';
        Universidade *aux = *inicio;

        // Percorrer as universidades ate encontrar um valor de aux que tenha o nome da universidade
        while (aux->prox != NULL)
        {

            if (strcmp(aux->prox->nome, universidadeName) == 0)
            {
                break;
            }
            aux = aux->prox;
        }
        aux->prox->nome[strlen(aux->prox->nome) + 1] = '\0';
        printf("a");
        if (aux->prox == NULL && strcmp(aux->prox->nome, universidadeName) != 0 || strcmp(aux->prox->nome, universidadeName) != 0)
        {
            printf("Universidade nao encontrada!\n");
            return;
        }
        // Percorrer todos os alunos e ir dando free neles!
        Aluno *aux_Aluno = aux->prox->inicioAluno;
        Aluno *aux_Aluno_anterior = aux->prox->inicioAluno;
        if (aux_Aluno != NULL)
        {
            while (aux_Aluno->prox != NULL)
            {
                aux_Aluno_anterior = aux_Aluno;
                aux_Aluno = aux_Aluno->prox;
                free(aux_Aluno_anterior);
            }
        }
        Universidade *aux2 = aux->prox;
        aux->prox = aux->prox->prox;
        
        printf("Universidade %s Deletada!",aux2->nome);
        free(aux2);
        imprime(*inicio);
    }
}

Universidade *recuperaDados(Universidade **inicio)
{
    FILE *file = fopen("lista_uni.txt", "r");
    if (file == NULL)
    {
        printf("Arquivo inexistente, sera criado.\n");
        return NULL;
    }

    Universidade *auxUniv = NULL;
    Aluno *auxAluno = NULL;
    char line[30];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            auxUniv->prox = NULL;
            auxUniv = NULL;
            auxAluno = NULL;
        }
        else if (auxUniv == NULL)
        {
            // Create a new university entry
            Universidade *nova_uni = malloc(sizeof(Universidade));
            strcpy(nova_uni->nome, line);

            fgets(line, sizeof(line), file);
            nova_uni->qtdAlunos = atoi(line);

            nova_uni->prox = NULL;
            nova_uni->inicioAluno = NULL;

            if (*inicio == NULL)
            {
                *inicio = nova_uni;
            }
            else
            {
                auxUniv = *inicio;
                while (auxUniv->prox != NULL)
                {
                    auxUniv = auxUniv->prox;
                }
                auxUniv->prox = nova_uni;
            }
            auxUniv = nova_uni;
        }
        else
        {
            // Create a new student entry
            Aluno *novo_aluno = malloc(sizeof(Aluno));
            strcpy(novo_aluno->nome, line);

            fgets(line, sizeof(line), file);
            novo_aluno->matricula = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->idade = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->nroDisciplinas = atoi(line);

            novo_aluno->prox = NULL;

            if (auxAluno == NULL)
            {
                auxUniv->inicioAluno = novo_aluno;
            }
            else
            {
                auxAluno->prox = novo_aluno;
            }
            auxAluno = novo_aluno;
        }
    }

    fclose(file);
    return *inicio;
}

int main()
{
    Universidade *inicio = NULL;
    int op = 10;
    recuperaDados(&inicio);
    salvaDados(inicio);
    char nome[30];

    while (op != 0)
    {
        printf("\n\nMenu:\n1.Inserir Uma Nova Unverdidade\n2.Inserir Aluno\n3.Busca Universidade\n4.Busca Aluno\n5.Remove Universidade\n6.Remover Aluno\n0.Fechar\n");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            salvaDados(inicio);
            break;
        case 1:
            insereU(&inicio, nome, 0);
            fflush(stdin);
            salvaDados(inicio);
            imprimeU(inicio);
            break;
        case 2:
            insereA(&inicio, nome, 0);
            salvaDados(inicio);
            imprimeA(inicio);
            break;
        case 3:
            buscaUniversidade(inicio, nome);
            break;
        case 4:
            buscaAluno(inicio, nome);
            break;
        case 5:
            removerUniversidade(&inicio);
            imprimeU(inicio);
            salvaDados(inicio);
            break;
        case 6:
            removerAluno(&inicio);
            imprimeA(inicio);
            salvaDados(inicio);
            break;
        default:
            printf("Menu:\n1.Inserir Uma Nova Unverdidade\n2.Inserir Aluno\n3.Busca Universidade\n4.Busca Aluno\n5.Remove Universidade\n6.Remover Aluno\n0.Fechar\n");
        }
    }
    return 0;
}