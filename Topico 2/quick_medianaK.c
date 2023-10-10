#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarVetorAleatorio(int arr[], int N)
{
    srand(time(NULL));
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

int encontrarMedianaK(int arr[], int esquerda, int direita, int k, long long *comparacoes)
{
    int tamanho = direita - esquerda + 1;
    int *valores = malloc(k * sizeof(int));

    for (int i = 0; i < k; i++)
    {
        valores[i] = arr[esquerda + rand() % tamanho];
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            (*comparacoes)++;
            if (valores[i] > valores[j])
            {
                trocar(&valores[i], &valores[j]);
            }
        }
    }

    int mediana = valores[k / 2];
    free(valores);
    return mediana;
}

int particionarMedianaK(int arr[], int esquerda, int direita, int k, long long *comparacoes, long long *trocas)
{
    int mediana = encontrarMedianaK(arr, esquerda, direita, k, comparacoes);

    for (int i = esquerda; i <= direita; i++)
    {
        if (arr[i] == mediana)
        {
            (*trocas)++;
            trocar(&arr[esquerda], &arr[i]);
            break;
        }
    }

    int pivot = arr[esquerda];
    int iMenor = esquerda;

    for (int i = esquerda + 1; i <= direita; i++)
    {
        (*comparacoes)++;
        if (arr[i] < pivot)
        {
            (*trocas)++;
            iMenor++;
            trocar(&arr[iMenor], &arr[i]);
        }
    }

    (*trocas)++;
    trocar(&arr[esquerda], &arr[iMenor]);

    return iMenor;
}

void quicksortMedianaK(int arr[], int esquerda, int direita, int k, long long *comparacoes, long long *trocas)
{
    if (esquerda < direita)
    {
        int indicePivo = particionarMedianaK(arr, esquerda, direita, k, comparacoes, trocas);

        quicksortMedianaK(arr, esquerda, indicePivo - 1, k, comparacoes, trocas);
        quicksortMedianaK(arr, indicePivo + 1, direita, k, comparacoes, trocas);
    }
}

int main()
{
    int n, k;
    printf("Digite o tamanho do vetor N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    gerarVetorAleatorio(arr, n);
    printf("Digite o valor de k para a mediana: ");
    scanf("%d", &k);

    if (k <= 0 || k > n)
    {
        printf("Valor de k inválido.\n");
        free(arr);
        return 1;
    }

    long long comparacoes = 0;
    long long trocas = 0;

    clock_t inicio_execucao = clock();

    quicksortMedianaK(arr, 0, n - 1, k, &comparacoes, &trocas);

    clock_t fim_execucao = clock();
    double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Comparacoes: %lld\n", comparacoes);
    printf("Trocas: %lld\n", trocas);
    printf("Tempo: %.4f segundos\n", tempo_execucao);

    free(arr);

    return 0;
}
