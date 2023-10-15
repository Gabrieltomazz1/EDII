#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarVetorAleatorio(int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 99
    }
}

void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arr[], int esquerda, int direita, long long int *comparacoes, long long int *trocas)
{
    int pivot = arr[direita];
    int i = (esquerda - 1);

    for (int j = esquerda; j <= direita - 1; j++)
    {
        (*comparacoes)++;
        if (arr[j] < pivot)
        {
            i++;
            trocar(&arr[i], &arr[j]);
            (*trocas)++;
        }
    }

    trocar(&arr[i + 1], &arr[direita]);
    (*trocas)++;
    return (i + 1);
}

void quicksortIterativo(int arr[], int esquerda, int direita, long long int *comparacoes, long long int *trocas)
{
    int *pilha = (int *)malloc(sizeof(int) * (direita - esquerda + 1));
    int topo = -1;

    pilha[++topo] = esquerda;
    pilha[++topo] = direita;

    while (topo >= 0)
    {
        direita = pilha[topo--];
        esquerda = pilha[topo--];

        int indicePivo = particionar(arr, esquerda, direita, comparacoes, trocas);

        if (indicePivo - 1 > esquerda)
        {
            pilha[++topo] = esquerda;
            pilha[++topo] = indicePivo - 1;
        }

        if (indicePivo + 1 < direita)
        {
            pilha[++topo] = indicePivo + 1;
            pilha[++topo] = direita;
        }
    }

    free(pilha);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <tamanho_do_vetor_N>\n", argv[0]);
        return 1;
    }

    long long int n = atoll(argv[1]);
    int inicio = 0;

    if (n <= 0)
    {
        printf("Tamanho do vetor inválido.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    gerarVetorAleatorio(arr, n);

    for (int test = 0; test < 5; test++)
    {
        long long int comparacoes = 0;
        long long int trocas = 0;

        clock_t inicio_execucao = clock();

        quicksortIterativo(arr, inicio, n - 1, &comparacoes, &trocas);

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        printf("Teste %d:\n", test + 1);
        printf("Comparacoes: %lld\n", comparacoes);
        printf("Trocas: %lld\n", trocas);
        printf("Tempo: %.4f segundos\n", tempo_execucao);
    }

    free(arr);

    return 0;
}
