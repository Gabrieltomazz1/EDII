#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>

typedef struct Detalhes{

int comps;                /* Quantidade de comparacoes */
int trocas;               /* Quantidade de trocas */

}detalhes;

void shellSort(int *vet, int tamanho,Detalhes *detalhes) {
    int i , j , value;
    int gap = 1;
    
    detalhes->trocas=0;
    detalhes->comps=0;
    
    while(gap < tamanho) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
    	
        gap /= 3;
        for(i = gap; i < tamanho; i++) { 
			detalhes->comps++;       	
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
                detalhes->trocas++;
            }
            vet [j + gap] = value;
        }
    }
}

int main (){

int n, i, *v;
int filho =i*2+1;
Detalhes detalhes;

printf ("\n Digite o valor de N:");
scanf ("%d",&n);
printf ("\n");

//GERA O VETOR ALEATORIO//
srand(time(NULL));
v= (int *) malloc (n*sizeof(int));
for(i = 0; i < n; i++){
v[i] = rand() % 100;
}
//IMPRIME O VETOR//
//for (i=0;i<n;i++){
//	printf (" %d",v[i]);
//}
printf ("\n");

// INICIA A CONTAGEM DO TEMPO //
 clock_t tempo;
 tempo = clock();
 
shellSort(v,n,&detalhes);

//IMPRIME VETOR ORDENADO//
//	printf ("\n");
//	for(int i = 0; i<n; i++){
//		printf(" %d", v[i]);
//	}

printf ("\n");
//IMPRIME O RESULTADO DAS COMPARACAOES//
printf ("\nN: %d",n);
printf ("\n");
printf ("Comparacoes: %d",detalhes.comps);
printf ("\n");
printf ("Trocas: %d",detalhes.trocas);
printf ("\n");

// IMPRIME O TEMPO //
for( i = 0; i < 99999999; ++i){}
	//fim
	printf("\nTempo:%f",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}     

