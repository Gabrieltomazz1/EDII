#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>

typedef struct Detalhes
{

	int comps;	/* Quantidade de comparacoes */
	int trocas; /* Quantidade de trocas */

} detalhes;

void criaHeap(int *v, int i, int filho, Detalhes *detalhes)
{

	int aux = v[i];
	int j = i * 2 + 1;
	// j � o pai;

	while (j <= filho)
	{
		if (j < filho)
		{
			detalhes->comps++;
			if (v[j] < v[j + 1])
			{
				j = j + 1;
			}
		}
		if (aux < v[j])
		{
			detalhes->comps++;
			v[i] = v[j];
			i = j;
			detalhes->trocas++;
			j = 2 * i + 1;
		}
		else
		{
			j = filho + 1;
		}
	}
	v[i] = aux;
	detalhes->trocas++;
}

void heapSort(int *v, int n, Detalhes *detalhes)
{

	detalhes->comps = 0;
	detalhes->trocas = 0;

	int i, aux;
	for (i = (n - 1) / 2; i >= 0; i--)
	{
		criaHeap(v, i, n - 1, detalhes);
	}
	for (i = (n - 1); i >= 1; i--)
	{
		aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		detalhes->trocas++;
		criaHeap(v, 0, i - 1, detalhes);
	}
}

int main()
{

	int n, i, *v;
	int filho = i * 2 + 1;
	Detalhes detalhes;

	printf("\n Digite o valor de N:");
	scanf("%d", &n);
	printf("\n");

	// GERA O VETOR ALEATORIO//
	srand(time(NULL));
	v = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		v[i] = rand() % 100;
	}
	// IMPRIME O VETOR//
	// for (i=0;i<n;i++){
	//	printf (" %d",v[i]);
	// }

	// INICIA A CONTAGEM DO TEMPO //
	clock_t tempo;
	tempo = clock();

	criaHeap(v, 0, filho, &detalhes);
	heapSort(v, n, &detalhes);

	// IMPRIME VETOR ORDENADO//
	//	printf ("\n");
	//	for(int i = 0; i<n; i++){
	//			printf(" %d", v[i]);
	//	}

	printf("\n");
	// IMPRIME O RESULTADO DAS COMPARACAOES//
	printf("\nN: %d", n);
	printf("\n");
	printf("Comparacoes: %d", detalhes.comps);
	printf("\n");
	printf("Trocas: %d", detalhes.trocas);
	printf("\n");

	// IMPRIME O TEMPO //
	for (i = 0; i < 99999999; ++i)
	{
	}
	// fim
	printf("\nTempo:%f", (clock() - tempo) / (double)CLOCKS_PER_SEC);
}
