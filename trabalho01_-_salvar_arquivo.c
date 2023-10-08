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
void imprimeA(Aluno *head)
{
    if (head == NULL)
    {
        printf("Lista vazia");
        return;
    }

    Universidade *aux = head;
    while (aux != NULL)
    {
        printf("Nome: %s\n", aux->nome);
        printf("Matrícula: %d\n", aux->matricula);
        printf("Idade: %d\n", aux->idade);
        printf("Quantidade de Matérias: %d\n\n\n", aux->nroDisciplinas);
        aux = aux->prox;
    }
}
//TODO universidades iguais?
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
//TODO Inserir ALuno
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
        printf("Insira o nome da Universidade: ");
        char nome[30];
        scanf("%s", &nome);
        getchar();
        Universidade *aux = *inicio;
        nome[strcspn(nome, "\n")] = '\0';
        aux->nome[strcspn(aux->nome, "\n")] = '\0';
        // Verificar se a Universidade eh a primeira
        if (strcmp(aux->nome, nome) == 0)
        {
            *inicio = aux->prox;
            printf("Universidade %s Removida!\n", aux->nome);
            free(aux);
            // Se nao for no inicio:
        }
        else
        {
            // Verificar se esta entre 2 outras Universidades
            while (aux->prox != NULL)
            {
                aux->prox->nome[strcspn(aux->prox->nome, "\n")] = '\0';
                // Pegar o anterior do ponteiro para a variavel que queremos remover
                if (strcmp(aux->prox->nome, nome) == 0)
                {
                    break;
                }
                aux = aux->prox;
            }
            if (aux->prox == NULL && strcmp(aux->nome, nome) != 0)
            {
                printf("Universidade nao encontrada!\n");
                return;
            }
            // Verificar se essa aux nao eh igual ao valor que queremos deletar, neste caso, vendo se nao existe!
            if (aux->prox->prox == NULL && strcmp(aux->prox->nome, nome) != 0)
            {
                printf("Universidade nao encontrada!\n");
                return;
            }
            printf("1a");
            // Criando uma variavel para armazenar o endereco da universidade que queremos deletar!
            Universidade *aux2 = aux->prox;
            // Caso existe um prox da aux que queremos deletar
            if (aux->prox->prox != NULL)
            {
                aux->prox = aux->prox->prox;
                printf("Universidade %s Removida!\n", aux2->nome);
                free(aux2);
                return;
            }
            else
            {
                aux->prox = NULL;
                printf("Universidade %s Removida!\n", aux2->nome);
                free(aux2);
            }
        }
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