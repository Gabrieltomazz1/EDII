#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0; // Variável para contar comparações
int trocas = 0;      // Variável para contar trocas

// Função para trocar dois elementos em um vetor
void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++; // Incrementa o contador de trocas
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
            comparacoes++; // Incrementa o contador de comparações
            trocas++;      // Incrementa o contador de trocas
        }
        arr[j + 1] = chave;
        trocas++; // Incrementa o contador de trocas
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
        comparacoes++; // Incrementa o contador de comparações
    }
    trocar(&arr[iMenor + 1], &arr[direita]);
    trocas++; // Incrementa o contador de trocas
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