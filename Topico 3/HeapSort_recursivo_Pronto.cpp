#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criaHeap(int *v, int i, int filho, int *comparacoes, int *trocas)
{
	int aux = v[i];
	int j = i * 2 + 1;

	while (j <= filho)
	{
		(*comparacoes)++;
		if (j < filho && v[j] < v[j + 1])
		{
			j = j + 1;
		}
		if (aux < v[j])
		{
			(*comparacoes)++;
			v[i] = v[j];
			i = j;
			(*trocas)++;
			j = 2 * i + 1;
		}
		else
		{
			j = filho + 1;
		}
	}
	v[i] = aux;
	(*trocas)++;
}

void heapSort(int *v, int n, int *comparacoes, int *trocas)
{
	*comparacoes = 0;
	*trocas = 0;

	int i, aux;
	for (i = (n - 1) / 2; i >= 0; i--)
	{
		criaHeap(v, i, n - 1, comparacoes, trocas);
	}
	for (i = (n - 1); i >= 1; i--)
	{
		aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		(*trocas)++;
		criaHeap(v, 0, i - 1, comparacoes, trocas);
	}
}

int main(int argc, char *argv[])
{
	int n, i, *v;
	int filho = i * 2 + 1;
	int comparacoes, trocas;

	if (argc != 2)
	{
		printf("Uso: %s <tamanho do vetor>\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);
	v = (int *)malloc(n * sizeof(int));
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		v[i] = rand() % 100;
	}

	// Executa cinco testes
	for (int test = 0; test < 5; test++)
	{
		printf("Teste %d!\n", test + 1);

		// Inicia a contagem do tempo
		clock_t tempo;
		tempo = clock();

		heapSort(v, n, &comparacoes, &trocas);

		printf("Tempo: %f segundos\n", (clock() - tempo) / (double)CLOCKS_PER_SEC);
		printf("Comparacoes: %d\n", comparacoes);
		printf("Trocas: %d\n", trocas);
	}

	free(v);

	return 0;
}
