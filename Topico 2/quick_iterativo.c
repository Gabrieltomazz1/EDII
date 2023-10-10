#include <stdio.h>
#include <stdlib.h>

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função de particionamento
int particionar(int arr[], int esquerda, int direita)
{
    int pivot = arr[esquerda];
    int i = esquerda;

    for (int j = esquerda + 1; j <= direita; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }

    trocar(&arr[i], &arr[esquerda]);
    return i;
}

// Função Quicksort Iterativo
void quicksortIterativo(int arr[], int esquerda, int direita)
{
    // Cria uma pilha para armazenar os limites esquerdo e direito das partições
    int pilha[direita - esquerda + 1];
    int topo = -1;

    // Inicializa a pilha com os limites da partição inicial
    pilha[++topo] = esquerda;
    pilha[++topo] = direita;

    // Enquanto a pilha não estiver vazia, continue a ordenação
    while (topo >= 0)
    {
        // Desempilhe os limites esquerdo e direito da pilha
        direita = pilha[topo--];
        esquerda = pilha[topo--];

        // Encontre o índice do pivô e coloque o pivô na posição correta
        int indicePivo = particionar(arr, esquerda, direita);

        // Se houver elementos à esquerda do pivô, empilhe os limites esquerdo e direito da subpartição
        if (indicePivo - 1 > esquerda)
        {
            pilha[++topo] = esquerda;
            pilha[++topo] = indicePivo - 1;
        }

        // Se houver elementos à direita do pivô, empilhe os limites esquerdo e direito da subpartição
        if (indicePivo + 1 < direita)
        {
            pilha[++topo] = indicePivo + 1;
            pilha[++topo] = direita;
        }
    }
}

int main()
{
    int n;
    printf("Digite o tamanho do vetor N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Chamada do Quicksort Iterativo
    quicksortIterativo(arr, 0, n - 1);

    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
