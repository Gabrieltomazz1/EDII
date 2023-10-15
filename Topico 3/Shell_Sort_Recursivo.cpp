#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Detalhes
{
    int comps;  /* Quantidade de comparações */
    int trocas; /* Quantidade de trocas */
} detalhes;

void shellSort(int *vet, int tamanho, detalhes *detalhes)
{
    int i, j, value;
    int gap = 1;

    detalhes->trocas = 0;
    detalhes->comps = 0;

    while (gap < tamanho)
    {
        gap = 3 * gap + 1;
    }
    while (gap > 1)
    {
        gap /= 3;
        for (i = gap; i < tamanho; i++)
        {
            detalhes->comps++;
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j])
            {
                vet[j + gap] = vet[j];
                j -= gap;
                detalhes->trocas++;
            }
            vet[j + gap] = value;
        }
    }
}

int main(int argc, char *argv[])
{
    int n, i, *v;
    detalhes detalhes;

    if (argc != 2)
    {
        printf("Uso: %s <tamanho do vetor>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    // Aloca e gera o vetor aleatório uma vez
    v = (int *)malloc(n * sizeof(int));
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        v[i] = rand() % 100;
    }

    // Executa cinco testes com o mesmo vetor
    for (int test = 0; test < 5; test++)
    {
        printf("Teste %d - Tamanho do vetor: %d\n", test + 1, n);

        // Inicia a contagem do tempo
        clock_t tempo_inicio = clock();

        shellSort(v, n, &detalhes);

        // Finaliza a contagem do tempo
        clock_t tempo_fim = clock();
        double tempo_execucao = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;

        // Calcula e imprime o tempo
        printf("Tempo: %f segundos\n", tempo_execucao);
        printf("Comparacoes: %d\n", detalhes.comps);
        printf("Trocas: %d\n", detalhes.trocas);
    }
    free(v);

    return 0;
}
