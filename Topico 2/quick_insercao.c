#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes_total = 0; // Variável para contar comparações totais
int trocas_total = 0;      // Variável para contar trocas totais
double tempo_total = 0;    // Variável para contar o tempo total

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas_total++; // Incrementa o contador de trocas totais
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
            comparacoes_total++; // Incrementa o contador de comparações totais
            trocas_total++;      // Incrementa o contador de trocas totais
        }
        arr[j + 1] = chave;
        trocas_total++; // Incrementa o contador de trocas totais
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
        comparacoes_total++; // Incrementa o contador de comparações totais
    }
    trocar(&arr[iMenor + 1], &arr[direita]);
    trocas_total++; // Incrementa o contador de trocas totais
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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Uso: %s <tamanho_do_vetor_N> <nome_do_arquivo_de_saida> <valor_de_m>\n", argv[0]);
        return 1;
    }

    long long int n = atoll(argv[1]);
    int m = atoi(argv[3]);
    int inicio = 0;

    if (n <= 0)
    {
        printf("Tamanho do vetor inválido.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    // Gere o vetor aleatório apenas uma vez
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100; // Valores aleatórios de 0 a 99
    }

    // Abrir o arquivo de saída
    FILE *arquivoSaida = fopen(argv[2], "w");

    for (int test = 0; test < 5; test++)
    {
        comparacoes_total = 0; // Zere os contadores totais a cada teste
        trocas_total = 0;

        clock_t inicio_execucao = clock();

        quicksortInsercao(arr, inicio, n - 1, m);

        clock_t fim_execucao = clock();
        double tempo_execucao = (double)(fim_execucao - inicio_execucao) / CLOCKS_PER_SEC;

        // Acumular as comparações, trocas e tempo para o total
        comparacoes_total += comparacoes_total;
        trocas_total += trocas_total;
        tempo_total += tempo_execucao;

        // Imprimir comparações, trocas e tempo para este teste no arquivo
        fprintf(arquivoSaida, "Teste %d:\n", test + 1);
        fprintf(arquivoSaida, "Comp: %d\n", comparacoes_total);
        fprintf(arquivoSaida, "Trocas: %d\n", trocas_total);
        fprintf(arquivoSaida, "Tempo: %.4f segundos\n", tempo_execucao);
    }

    // Calcular a média das comparações, trocas e tempo
    int media_comparacoes = comparacoes_total / 5;
    int media_trocas = trocas_total / 5;
    double media_tempo = tempo_total / 5;

    // Escrever os resultados da média no arquivo de saída
    fprintf(arquivoSaida, "Média de Comp: %d\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de trocas: %d\n", media_trocas);
    fprintf(arquivoSaida, "Média de Temp: %f segundos\n", media_tempo);
    fprintf(arquivoSaida, "Valor de m %d", m);
    fclose(arquivoSaida);
    free(arr);

    return 0;
}
