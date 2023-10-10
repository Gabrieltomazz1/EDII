#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para encontrar a mediana de k elementos
int encontrarMedianaK(int arr[], int esquerda, int direita, int k)
{
    int tamanho = direita - esquerda + 1;
    int *valores = malloc(k * sizeof(int));

    // Escolher aleatoriamente k elementos como candidatos a pivô
    for (int i = 0; i < k; i++)
    {
        valores[i] = arr[esquerda + rand() % tamanho];
    }

    // Ordenar os valores
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
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

// Função de particionamento usando a mediana de k elementos como pivô
int particionarMedianaK(int arr[], int esquerda, int direita, int k)
{
    int mediana = encontrarMedianaK(arr, esquerda, direita, k);

    // Trocar a mediana com o elemento na posição 'esquerda' para usá-lo como pivô
    for (int i = esquerda; i <= direita; i++)
    {
        if (arr[i] == mediana)
        {
            trocar(&arr[esquerda], &arr[i]);
            break;
        }
    }

    int pivot = arr[esquerda];
    int iMenor = esquerda;

    // Particionar o vetor
    for (int i = esquerda + 1; i <= direita; i++)
    {
        if (arr[i] < pivot)
        {
            iMenor++;
            trocar(&arr[iMenor], &arr[i]);
        }
    }

    // Colocar o pivô na posição correta
    trocar(&arr[esquerda], &arr[iMenor]);

    return iMenor;
}

// Função Quicksort Mediana(k)
void quicksortMedianaK(int arr[], int esquerda, int direita, int k)
{
    if (esquerda < direita)
    {
        int indicePivo = particionarMedianaK(arr, esquerda, direita, k);

        // Recursivamente ordenar as duas partes
        quicksortMedianaK(arr, esquerda, indicePivo - 1, k);
        quicksortMedianaK(arr, indicePivo + 1, direita, k);
    }
}

int main()
{
    int n, k;
    printf("Digite o tamanho do vetor N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Digite o valor de k para a mediana: ");
    scanf("%d", &k);

    quicksortMedianaK(arr, 0, n - 1, k);

    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
