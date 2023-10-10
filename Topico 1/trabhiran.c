#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0; // Variável para contar comparações
int trocas = 0;      // Variável para contar trocas

// Função para gerar um vetor aleatório de tamanho N
void gerarVetorAleatorio(int arr[], int N)
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 999
    }
}

// Função para imprimir um vetor
void imprimirVetor(int arr[], int N)
{
    printf("Vetor: ");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função para imprimir estatísticas
void imprimirEstatisticas()
{
    printf("Numero de comparacoes: %d\n", comparacoes);
    printf("Numero de trocas: %d\n", trocas);
}

// Função para mesclar dois subvetores em um vetor ordenado
void merge(int arr[], int esq, int meio, int dir)
{
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int esqArray[n1];
    int dirArray[n2];

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
    int contador = 1;

    while (1) 
    {
        printf("Digite o valor de N (ou 0 para sair): \n");
        scanf("%d", &N);

        if (N == 0)
        {
            break; // Sai do loop se o usuário digitar 0
        }

        int arr[N];

        gerarVetorAleatorio(arr, N);

        printf("Execucao %d:\n", contador);

        // Registrar o tempo de início
        clock_t start_time = clock();

        mergeSort(arr, 0, N - 1);

        // Registrar o tempo de término
        clock_t end_time = clock();

        // Calcular o tempo de execução em segundos
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        imprimirVetor(arr,N);
        printf("Tempo de execucao: %f segundos\n", execution_time * 1000);
        imprimirEstatisticas();
        contador++;
    }

    return 0;
}
