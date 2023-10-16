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
	int comparacoes_total = 0;
	int trocas_total = 0;
	double tempo_total = 0.0;

	if (argc != 3)
	{
		printf("Uso: %s <tamanho do vetor> <nome do arquivo de saída>\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);
	v = (int *)malloc(n * sizeof(int));
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		v[i] = rand() % 100;
	}

	// Abrir o arquivo de saída
	FILE *arquivoSaida = fopen(argv[2], "w");

	// Executa cinco testes
	for (int test = 0; test < 5; test++)
	{
		int comparacoes = 0;
		int trocas = 0;

		fprintf(arquivoSaida, "Teste %d:\n", test + 1);

		// Inicia a contagem do tempo
		clock_t tempo;
		tempo = clock();

		heapSort(v, n, &comparacoes, &trocas);

		double execution_time = (clock() - tempo) / (double)CLOCKS_PER_SEC;

		fprintf(arquivoSaida, "Tempo: %f segundos\n", execution_time);
		fprintf(arquivoSaida, "Comparacoes: %d\n", comparacoes);
		fprintf(arquivoSaida, "Trocas: %d\n", trocas);

		// Acumular as comparações, trocas e tempo para o total
		comparacoes_total += comparacoes;
		trocas_total += trocas;
		tempo_total += execution_time;
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
	free(v);

	return 0;
}
