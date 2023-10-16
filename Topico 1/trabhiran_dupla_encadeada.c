#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void freeList(struct Node *head)
{
    while (head != NULL)
    {
        struct Node *current = head;
        head = head->next;
        free(current);
    }
}

struct Node *merge(struct Node *left, struct Node *right, int *comparacoes, int *trocas)
{
    if (left == NULL)
    {
        return right;
    }
    if (right == NULL)
    {
        return left;
    }

    struct Node *result = NULL;

    if (left->data <= right->data)
    {
        result = left;
        result->next = merge(left->next, right, comparacoes, trocas);
        if (result->next)
        {
            result->next->prev = result;
        }
    }
    else
    {
        result = right;
        result->next = merge(left, right->next, comparacoes, trocas);
        if (result->next)
        {
            result->next->prev = result;
        }

        // Incrementa o número de trocas
        (*trocas)++;
    }

    (*comparacoes)++;

    return result;
}

struct Node *mergeSort(struct Node *head, int *comparacoes, int *trocas)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct Node *middle = head;
    struct Node *fast = head->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            middle = middle->next;
        }
    }

    struct Node *left = head;
    struct Node *right = middle->next;
    middle->next = NULL;

    left = mergeSort(left, comparacoes, trocas);
    right = mergeSort(right, comparacoes, trocas);

    struct Node *mergedList = merge(left, right, comparacoes, trocas);

    return mergedList;
}

struct Node *createRandomList(int N)
{
    struct Node *head = newNode(rand() % 1000);
    struct Node *current = head;
    for (int i = 1; i < N; i++)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = rand() % 1000;
        newNode->prev = current;
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <tamanho_inicial_da_lista> <nome_do_arquivo_de_saida>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    char *nomeArquivoSaida = argv[2]; // Obtemos o nome do arquivo de saída

    srand(time(NULL));
    struct Node *head = createRandomList(N);

    int total_comparacoes = 0;
    int total_trocas = 0;
    double total_tempo_execucao = 0.0;

    FILE *arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL)
    {
        printf("Não foi possível abrir o arquivo de saída.\n");
        return 1;
    }

    for (int test = 1; test <= 5; test++)
    {
        fprintf(arquivoSaida, "Teste %d - Tamanho da lista: %d\n", test, N);

        clock_t start_time = clock();
        int comparacoes = 0;
        int trocas = 0;

        head = mergeSort(head, &comparacoes, &trocas);

        clock_t end_time = clock();

        double tempo_execucao = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        fprintf(arquivoSaida, "Teste %d:\n", test);
        fprintf(arquivoSaida, "Comparacoes: %d\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %d\n", trocas);
        fprintf(arquivoSaida, "Tempo: %.4f segundos\n", tempo_execucao);

        total_comparacoes += comparacoes;
        total_trocas += trocas;
        total_tempo_execucao += tempo_execucao;

        freeList(head);
        head = createRandomList(N); // Recria a lista para o próximo teste
    }

    double media_comparacoes = (double)total_comparacoes / 5;
    double media_trocas = (double)total_trocas / 5;
    double media_tempo_execucao = total_tempo_execucao / 5;

    fprintf(arquivoSaida, "Média de Comparacoes: %.2f\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de Trocas: %.2f\n", media_trocas);
    fprintf(arquivoSaida, "Média de Tempo de Execução: %.4f segundos\n", media_tempo_execucao);

    fclose(arquivoSaida);

    return 0;
}
