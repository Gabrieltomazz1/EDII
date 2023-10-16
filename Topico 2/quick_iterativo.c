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

void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arr[], int esquerda, int direita, long long int *comparacoes, long long int *trocas)
{
    int pivot = arr[direita];
    int i = (esquerda - 1);

    for (int j = esquerda; j <= direita - 1; j++)
    {
        (*comparacoes)++;
        if (arr[j] < pivot)
        {
            i++;
            trocar(&arr[i], &arr[j]);
            (*trocas)++;
        }
    }

    trocar(&arr[i + 1], &arr[direita]);
    (*trocas)++;
    return (i + 1);
}

void quicksortIterativo(int arr[], int esquerda, int direita, long long int *comparacoes, long long int *trocas)
{
    int *pilha = (int *)malloc(sizeof(int) * (direita - esquerda + 1));
    int topo = -1;

    pilha[++topo] = esquerda;
    pilha[++topo] = direita;

    while (topo >= 0)
    {
        direita = pilha[topo--];
        esquerda = pilha[topo--];

        int indicePivo = particionar(arr, esquerda, direita, comparacoes, trocas);

        if (indicePivo - 1 > esquerda)
        {
            pilha[++topo] = esquerda;
            pilha[++topo] = indicePivo - 1;
        }

        if (indicePivo + 1 < direita)
        {
            pilha[++topo] = indicePivo + 1;
            pilha[++topo] = direita;
        }
    }

    free(pilha);
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <tamanho_do_vetor_N> <nome_do_arquivo_de_saida>\n", argv[0]);
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
    gerarVetorAleatorio(arr, n);

    // Abrir o arquivo de saída
    FILE *arquivoSaida = fopen(argv[2], "w");

    long long int comparacoes_total = 0;
    long long int trocas_total = 0;
    double tempo_total = 0;

    for (int test = 0; test < 5; test++)
    {
        long long int comparacoes = 0;
        long long int trocas = 0;

        clock_t inicio_execucao = clock();

        quicksortIterativo(arr, inicio, n - 1, &comparacoes, &trocas);

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes;
        trocas_total += trocas;
        tempo_total += tempo_execucao;

        // Imprimir comparações, trocas e tempo para este teste no arquivo
        fprintf(arquivoSaida, "Teste %d:\n", test + 1);
        fprintf(arquivoSaida, "Comp: %lld\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %lld\n", trocas);
        fprintf(arquivoSaida, "Tempo: %.4f segundos\n", tempo_execucao);
    }

    // Calcular a média das comparações, trocas e tempo
    long long int media_comparacoes = comparacoes_total / 5;
    long long int media_trocas = trocas_total / 5;
    double media_tempo = tempo_total / 5;

    // Escrever os resultados da média no arquivo de saída
    fprintf(arquivoSaida, "Média de Comp: %lld\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de trocas: %lld\n", media_trocas);
    fprintf(arquivoSaida, "Média de Temp: %f segundos\n", media_tempo);
    fclose(arquivoSaida);
    free(arr);

    return 0;
}
