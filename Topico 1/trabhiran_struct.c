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
// Função para gerar um número inteiro aleatório no intervalo [min, max]
int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Função para gerar uma string aleatória
void randomString(char *str, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length - 1; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\0'; // Terminador de string
}

// Função para gerar dados aleatórios
struct Dados gerarDadosAleatorios()
{
    struct Dados dados;

    // Gerar valores aleatórios para a chave e o booleano
    dados.key = randomInt(1, 1000);
    dados.boolean = randomInt(0, 1);

    // Gerar strings aleatórias
    for (int i = 0; i < 10; i++)
    {
        randomString(dados.strings[i], sizeof(dados.strings[i]));
    }

    // Gerar valores de ponto flutuante aleatórios
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

    struct Dados L[p1], R[p2];

    for (i = 0; i < p1; i++)
        L[i] = arr[esq + i];
    for (j = 0; j < p2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;
    while (i < p1 && j < p2)
    {
        // Atualize as comparações
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
        // Atualize as trocas
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

void printRecords(struct Dados arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Key: %d, Boolean: %d\n", arr[i].key, arr[i].boolean);
        printf("Strings: ");
        for (int j = 0; j < 10; j++)
        {
            printf("%s", arr[i].strings[j]);
            if (j < 9)
                printf(", ");
        }
        printf("\n");
        printf("Real: ");
        for (int j = 0; j < 4; j++)
        {
            printf("%.2f", arr[i].real[j]);
            if (j < 3)
                printf(", ");
        }
        printf("\n\n");
    }
}

int main()
{

    int n; // Tamanho do array de registros
    printf("Digite o tamanho da lista: ");
    scanf("%d", &n);
    struct Dados records[n];
    srand(time(NULL)); // Inicialize a semente do gerador de números aleatórios

    // Gerar registros aleatórios
    for (int i = 0; i < n; i++)
    {
        records[i] = gerarDadosAleatorios();
    }

    printf("Desordenado:\n");
    printRecords(records, n);

    mergeSort(records, 0, n - 1);

    printf("\nOrdenado:\n");
    printRecords(records, n);

    printf("\nDetalhes:\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);

    return 0;
}