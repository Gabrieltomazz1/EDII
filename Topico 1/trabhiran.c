#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0; // Variável para contar comparações
int trocas = 0;      // Variável para contar trocas

// Função para mesclar dois subvetores em um vetor ordenado
void merge(int arr[], int esq, int meio, int dir)
{
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *esqArray = (int *)malloc(n1 * sizeof(int));
    int *dirArray = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
    {
        esqArray[i] = arr[esq + i];
    }
    for (int j = 0; j < n2; j++)
    {
        dirArray[j] = arr[meio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = esq;

    while (i < n1 && j < n2)
    {
        comparacoes++; // Incrementa o contador de comparações
        if (esqArray[i] <= dirArray[j])
        {
            arr[k] = esqArray[i];
            i++;
        }
        else
        {
            arr[k] = dirArray[j];
            j++;
        }
        k++;
        trocas++; // Incrementa o contador de trocas
    }

    while (i < n1)
    {
        arr[k] = esqArray[i];
        i++;
        k++;
        trocas++; // Incrementa o contador de trocas
    }

    while (j < n2)
    {
        arr[k] = dirArray[j];
        j++;
        k++;
        trocas++; // Incrementa o contador de trocas
    }

    free(esqArray);
    free(dirArray);
}

// Função principal do Merge Sort
void mergeSort(int arr[], int esq, int dir)
{
    if (esq < dir)
    {
        int meio = esq + (dir - esq) / 2;
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
}

int main()
{
    int N;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 99
    }

    printf("Ordenando %d elementos...\n", N);

    // Registrar o tempo de início
    clock_t start_time = clock();

    mergeSort(arr, 0, N - 1);

    // Registrar o tempo de término
    clock_t end_time = clock();

    // Calcular o tempo de execução em segundos
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Tempo de execucao: %f segundos\n", execution_time);
    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);

    free(arr);

    return 0;
}
