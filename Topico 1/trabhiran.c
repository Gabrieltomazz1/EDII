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

void gerarVetorAleatorio(int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 99
    }
}
int main(int argc, char *argv[])
{
    int N;

    if (argc != 3)
    {
        printf("Uso: %s <tamanho do vetor> <nome do arquivo de saída>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1];
    char *nomeArquivoSaida = argv[2];

    FILE *arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL)
    {
        printf("Não foi possível abrir o arquivo de saída.\n");
        return 1;
    }

    int *arr = (int *)malloc(N * sizeof(int));

    srand(time(NULL));

    int comparacoes_total = 0;
    int trocas_total = 0;
    double tempo_total = 0.0;

    for (int test = 0; test < 5; test++)
    {
        // Gerar o vetor com valores aleatórios
        gerarVetorAleatorio(arr, N);

        // Registrar o tempo de início
        clock_t start_time = clock();

        mergeSort(arr, 0, N - 1);

        // Registrar o tempo de término
        clock_t end_time = clock();

        // Calcular o tempo de execução em segundos
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes;
        trocas_total += trocas;
        tempo_total += execution_time;

        // Imprimir comparações e tempo para este teste no arquivo
        fprintf(arquivoSaida, "Teste %d:\n", test + 1);
        fprintf(arquivoSaida, "Comparacoes: %d\n", comparacoes);
        fprintf(arquivoSaida, "Tempo: %f segundos\n", execution_time);

        // Limpar as variáveis de contagem
        comparacoes = 0;
        trocas = 0;
    }

    // Calcular a média das comparações, trocas e tempo
    int media_comparacoes = comparacoes_total / 5;
    int media_trocas = trocas_total / 5;
    double media_tempo = tempo_total / 5;

    // Escrever os resultados da média no arquivo de saída
    fprintf(arquivoSaida, "Média de comparações: %d\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de trocas: %d\n", media_trocas);
    fprintf(arquivoSaida, "Média de tempo: %f segundos\n", media_tempo);

    fclose(arquivoSaida);
    free(arr);

    return 0;
}
