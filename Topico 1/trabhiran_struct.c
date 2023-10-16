#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Dados
{
    int key;
    char strings[10][200];
    int boolean;
    float real[4];
};

int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void randomString(char *str, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length - 1; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\0';
}

struct Dados gerarDadosAleatorios()
{
    struct Dados dados;

    dados.key = randomInt(1, 1000);
    dados.boolean = randomInt(0, 1);

    for (int i = 0; i < 10; i++)
    {
        randomString(dados.strings[i], sizeof(dados.strings[i]));
    }

    for (int i = 0; i < 4; i++)
    {
        dados.real[i] = (float)rand() / RAND_MAX;
    }

    return dados;
}

void merge(struct Dados arr[], int esq, int meio, int dir, int *comparacoes, int *trocas)
{
    int i, j, k;
    int p1 = meio - esq + 1;
    int p2 = dir - meio;

    struct Dados *L = (struct Dados *)malloc(p1 * sizeof(struct Dados));
    struct Dados *R = (struct Dados *)malloc(p2 * sizeof(struct Dados));

    for (i = 0; i < p1; i++)
        L[i] = arr[esq + i];
    for (j = 0; j < p2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;
    while (i < p1 && j < p2)
    {
        (*comparacoes)++;
        if (L[i].key <= R[j].key)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        (*trocas)++;
    }

    while (i < p1)
    {
        arr[k] = L[i];
        i++;
        k++;
        (*trocas)++;
    }

    while (j < p2)
    {
        arr[k] = R[j];
        j++;
        k++;
        (*trocas)++;
    }

    free(L);
    free(R);
}

void mergeSort(struct Dados arr[], int esq, int dir, int *comparacoes, int *trocas)
{
    if (esq < dir)
    {
        int meio = esq + (dir - esq) / 2;

        mergeSort(arr, esq, meio, comparacoes, trocas);
        mergeSort(arr, meio + 1, dir, comparacoes, trocas);

        merge(arr, esq, meio, dir, comparacoes, trocas);
    }
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 3)
    {
        printf("Uso: %s <tamanho da lista> <nome do arquivo de saída>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    char *nomeArquivoSaida = argv[2];

    struct Dados *records = (struct Dados *)malloc(n * sizeof(struct Dados));
    srand(time(NULL));

    FILE *arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL)
    {
        printf("Não foi possível abrir o arquivo de saída.\n");
        return 1;
    }

    double media_comparacoes = 0.0;
    double media_trocas = 0.0;
    double media_tempo = 0.0;

    for (int test = 0; test < 5; test++)
    {
        int comparacoes = 0;
        int trocas = 0;

        clock_t start = clock();
        mergeSort(records, 0, n - 1, &comparacoes, &trocas);
        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(arquivoSaida, "Comparacoes: %d\n", comparacoes);
        fprintf(arquivoSaida, "Trocas: %d\n", trocas);
        fprintf(arquivoSaida, "Tempo: %f segundos\n", elapsed_time);

        media_comparacoes += comparacoes;
        media_trocas += trocas;
        media_tempo += elapsed_time;
    }

    media_comparacoes /= 5.0;
    media_trocas /= 5.0;
    media_tempo /= 5.0;

    fprintf(arquivoSaida, "\nMédia de Comparacoes: %.2f\n", media_comparacoes);
    fprintf(arquivoSaida, "Média de Trocas: %.2f\n", media_trocas);
    fprintf(arquivoSaida, "Média de Tempo: %.2f segundos\n", media_tempo);

    fclose(arquivoSaida);
    free(records);

    return 0;
}
