#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0;
int trocas = 0;

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

void merge(struct Dados arr[], int esq, int meio, int dir)
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
        comparacoes++;
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
        trocas++;
    }

    while (i < p1)
    {
        arr[k] = L[i];
        i++;
        k++;
        trocas++;
    }

    while (j < p2)
    {
        arr[k] = R[j];
        j++;
        k++;
        trocas++;
    }

    free(L);
    free(R);
}

void mergeSort(struct Dados arr[], int esq, int dir)
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
    int n;
    printf("Digite o tamanho da lista: ");
    scanf("%d", &n);
    struct Dados *records = (struct Dados *)malloc(n * sizeof(struct Dados));
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        records[i] = gerarDadosAleatorios();
    }

    mergeSort(records, 0, n - 1);

    printf("\nDetalhes:\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);

    free(records);

    return 0;
}
