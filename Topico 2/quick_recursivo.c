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

int particiona(int arr[], int inicio, int fim, long long int *comparacoes, long long int *trocas)
{
    int meio = (inicio + fim) / 2;
    int pivo = arr[meio];
    int esq = inicio - 1;
    int dir = fim + 1;

    while (1)
    {
        do
        {
            esq++;
            (*comparacoes)++;
        } while (arr[esq] < pivo);

        do
        {
            dir--;
            (*comparacoes)++;
        } while (arr[dir] > pivo);

        if (esq >= dir)
            return dir;

        // Troca arr[esq] e arr[dir]
        int temp = arr[esq];
        arr[esq] = arr[dir];
        arr[dir] = temp;
        (*trocas)++;
    }
}

// Função de ordenação Quick Sort
void quickSort(int arr[], int inicio, int fim, long long int *comparacoes, long long int *trocas)
{
    if (inicio < fim)
    {
        int pivo = particiona(arr, inicio, fim, comparacoes, trocas);
        quickSort(arr, inicio, pivo, comparacoes, trocas);
        quickSort(arr, pivo + 1, fim, comparacoes, trocas);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <valor_de_N>\n", argv[0]);
        return 1;
    }

    long long int n = atoll(argv[1]);
    int inicio = 0;
    int fim = n - 1;

    // Declaração e alocação de memória para o vetor
    int *arr = (int *)malloc(n * sizeof(int));

    // Gerar números aleatórios para preencher o vetor
    gerarVetorAleatorio(arr, n);

    for (int test = 1; test <= 5; test++)
    {
        printf("Teste %d\n", test);

        long long int comparacoes = 0;
        long long int trocas = 0;

        // Medir o tempo de execução
        clock_t inicio_execucao = clock();

        // Chamada da função de ordenação Quick Sort
        quickSort(arr, inicio, fim, &comparacoes, &trocas);

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        printf("\n");

        printf("Comparacoes: %lld\n", comparacoes);
        printf("Trocas: %lld\n", trocas);
        printf("Tempo: %.4f segundos\n", tempo_execucao);

        // Limpeza para o próximo teste
        if (test < 5)
        {
            // Regere o vetor aleatório para os próximos testes
            gerarVetorAleatorio(arr, n);
        }
    }

    // Liberar a memória alocada para o vetor
    free(arr);
}
