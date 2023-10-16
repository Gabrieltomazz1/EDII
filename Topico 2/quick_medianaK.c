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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Uso: %s <tamanho_do_vetor_N> <valor_de_k> <nome_do_arquivo_de_saida>\n", argv[0]);
        return 1;
    }

    int n, k;
    n = atoi(argv[1]);
    k = atoi(argv[2]);

    if (n <= 0)
    {
        printf("Tamanho do vetor inválido.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));

    // Abrir o arquivo de saída
    FILE *arquivoSaida = fopen(argv[3], "w");

    gerarVetorAleatorio(arr, n);

    if (k <= 0 || k > n)
    {
        printf("Valor de k inválido.\n");
        fclose(arquivoSaida);
        free(arr);
        return 1;
    }

    long long comparacoes_total = 0;
    long long trocas_total = 0;
    double tempo_total = 0;

    for (int i = 0; i < 5; i++)
    {
        clock_t inicio_execucao = clock();

        long long comparacoes = 0;
        long long trocas = 0;

        quicksortMedianaK(arr, 0, n - 1, k, &comparacoes, &trocas);

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes;
        trocas_total += trocas;
        tempo_total += tempo_execucao;

        // Imprimir comparações, trocas e tempo para este teste no arquivo
        fprintf(arquivoSaida, "Teste %d:\n", i + 1);
        fprintf(arquivoSaida, "Comp: %lld\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %lld\n", trocas);
        fprintf(arquivoSaida, "Tempp: %f segundos\n", tempo_execucao);
    }

    // Calcular a média das comparações, trocas e tempo
    long long int media_comparacoes = comparacoes_total / 5;
    long long int media_trocas = trocas_total / 5;
    double media_tempo = tempo_total / 5;

    // Escrever os resultados da média no arquivo de saída
    fprintf(arquivoSaida, "Média de Comp: %lld\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de trocas: %lld\n", media_trocas);
    fprintf(arquivoSaida, "Média de Temp: %f segundos\n", media_tempo);
    fprintf(arquivoSaida,"Valor de K %d",k);
    fclose(arquivoSaida);
    free(arr);

    return 0;
}
