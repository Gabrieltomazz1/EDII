#include <stdio.h>
#include <stdlib.h>

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
        }
        arr[j + 1] = chave;
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
    }
    trocar(&arr[iMenor + 1], &arr[direita]);
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

int main()
{
    int n, m;
    printf("Digite o tamanho do vetor N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Digite o valor de m para a estratégia de Inserção(m): ");
    scanf("%d", &m);

    quicksortInsercao(arr, 0, n - 1, m);

    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
