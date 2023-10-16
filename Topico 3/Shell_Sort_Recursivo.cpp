#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellSort(int *vet, int tamanho, int *comparacoes, int *trocas)
{
    int i, j, value;
    int gap = 1;

    *trocas = 0;
    *comparacoes = 0;

    while (gap < tamanho)
    {
        gap = 3 * gap + 1;
    }
    while (gap > 1)
    {
        gap /= 3;
        for (i = gap; i < tamanho; i++)
        {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j])
            {
                (*comparacoes)++;
                vet[j + gap] = vet[j];
                j -= gap;
                (*trocas)++;
            }
            vet[j + gap] = value;
        }
    }
}

int main(int argc, char *argv[])
{
    int n, i;
    double tempo_total = 0.0;
    int comparacoes_total = 0;
    int trocas_total = 0;

    if (argc != 3)
    {
        printf("Uso: %s <tamanho do vetor> <nome do arquivo de saída>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    srand(time(NULL));

    // Abrir o arquivo de saída
    FILE *arquivoSaida = fopen(argv[2], "w");

    // Executa cinco testes
    for (int test = 0; test < 5; test++)
    {
        int *v = (int *)malloc(n * sizeof(int));
        int comparacoes = 0;
        int trocas = 0;

        for (i = 0; i < n; i++)
        {
            v[i] = rand() % 100;
        }

        fprintf(arquivoSaida, "Teste %d:\n", test + 1);

        // Inicia a contagem do tempo
        clock_t tempo_inicio = clock();

        shellSort(v, n, &comparacoes, &trocas);

        // Finaliza a contagem do tempo
        clock_t tempo_fim = clock();
        double tempo_execucao = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;

        fprintf(arquivoSaida, "Tempo: %f segundos\n", tempo_execucao);
        fprintf(arquivoSaida, "Comparacoes: %d\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %d\n", trocas);

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes;
        trocas_total += trocas;
        tempo_total += tempo_execucao;

        free(v); // Libera o vetor alocado
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

    return 0;
}
