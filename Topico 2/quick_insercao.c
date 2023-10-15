#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0; // Variável para contar comparações
int trocas = 0;      // Variável para contar trocas

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++; // Incrementa o contador de trocas
}

// Função de Inserção para ordenar uma partição com tamanho <= m
void insercao(int arr[], int esquerda, int direita)
{
    for (int i = esquerda + 1; i <= direita; i++)
    {
        int chave = arr[i];
        int j = i - 1;
        while (j >= esquerda && arr[j] > chave)
        {
            arr[j + 1] = arr[j];
            j--;
            comparacoes++; // Incrementa o contador de comparações
            trocas++;      // Incrementa o contador de trocas
        }
        arr[j + 1] = chave;
        trocas++; // Incrementa o contador de trocas
    }
}

// Função de particionamento para o Quicksort com Inserção(m)
int particionar(int arr[], int esquerda, int direita)
{
    int pivot = arr[direita];
    int iMenor = (esquerda - 1);

    for (int j = esquerda; j <= direita - 1; j++)
    {
        if (arr[j] < pivot)
        {
            iMenor++;
            trocar(&arr[iMenor], &arr[j]);
        }
        comparacoes++; // Incrementa o contador de comparações
    }
    trocar(&arr[iMenor + 1], &arr[direita]);
    trocas++; // Incrementa o contador de trocas
    return (iMenor + 1);
}

// Função Quicksort com Inserção(m)
void quicksortInsercao(int arr[], int esquerda, int direita, int m)
{
    if (esquerda < direita)
    {
        if (direita - esquerda + 1 <= m)
        {
            insercao(arr, esquerda, direita); // Usar Inserção para partições pequenas
        }
        else
        {
            int indicePivo = particionar(arr, esquerda, direita);
            quicksortInsercao(arr, esquerda, indicePivo - 1, m);
            quicksortInsercao(arr, indicePivo + 1, direita, m);
        }
    }
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

    // Gere o vetor aleatório apenas uma vez
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 99
    }

    for (int test = 0; test < 5; test++)
    {
        comparacoes = 0; // Zere os contadores a cada teste
        trocas = 0;

        clock_t inicio_execucao = clock();

        quicksortInsercao(arr, inicio, n - 1, 10); // Mude o valor de 'm' conforme necessário

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        printf("Teste %d:\n", test + 1);
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n", trocas);
        printf("Tempo: %.4f segundos\n", tempo_execucao);
    }

    free(arr);

    return 0;
}
