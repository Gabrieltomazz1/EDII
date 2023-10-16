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
    if (argc != 3)
    {
        printf("Uso: %s <tamanho do vetor> <nome do arquivo de saída>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    char *nomeArquivoSaida = argv[2];

    FILE *arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL)
    {
        printf("Não foi possível abrir o arquivo de saída.\n");
        return 1;
    }

    int *arr = (int *)malloc(N * sizeof(int));

    srand(time(NULL));

    long long int comparacoes_total = 0;
    long long int trocas_total = 0;
    double tempo_total = 0.0;

    for (int test = 0; test < 5; test++)
    {
        // Gerar o vetor com valores aleatórios
        gerarVetorAleatorio(arr, N);

        long long int comparacoes = 0;
        long long int trocas = 0;

        // Registrar o tempo de início
        clock_t start_time = clock();

        // Chamada da função de ordenação Quick Sort
        quickSort(arr, 0, N - 1, &comparacoes, &trocas);

        // Registrar o tempo de término
        clock_t end_time = clock();

        // Calcular o tempo de execução em segundos
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes;
        trocas_total += trocas;
        tempo_total += execution_time;

        // Imprimir comparações, trocas e tempo para este teste no arquivo
        fprintf(arquivoSaida, "Teste %d:\n", test + 1);
        fprintf(arquivoSaida, "Comparacoes: %lld\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %lld\n", trocas);
        fprintf(arquivoSaida, "Tempo: %f segundos\n", execution_time);
    }

    // Calcular a média das comparações, trocas e tempo
    long long int media_comparacoes = comparacoes_total / 5;
    long long int media_trocas = trocas_total / 5;
    double media_tempo = tempo_total / 5;

    // Escrever os resultados da média no arquivo de saída
    fprintf(arquivoSaida, "Média de comparações: %lld\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de trocas: %lld\n", media_trocas);
    fprintf(arquivoSaida, "Média de tempo: %f segundos\n", media_tempo);

    fclose(arquivoSaida);
    free(arr);

    return 0;
}
