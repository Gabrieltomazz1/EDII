#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura de um nó da lista duplamente encadeada
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Variáveis globais para contar comparações e trocas
int comparacoes = 0;
int trocas = 0;

// Função para criar um novo nó
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Função para imprimir a lista
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Função para mesclar duas listas ordenadas em uma única lista ordenada
struct Node* merge(struct Node* left, struct Node* right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    struct Node* result = NULL;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
        result->next->prev = result;
    } else {
        result = right;
        result->next = merge(left, right->next);
        result->next->prev = result;
    }

    // Incrementar a variável global de comparações
    comparacoes++;

    return result;
}

// Função para contar o número de nós em uma lista
int countNodes(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Função principal do Merge Sort para listas encadeadas
struct Node* mergeSort(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node* middle = head;
    struct Node* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            middle = middle->next;
        }
    }

    struct Node* left = head;
    struct Node* right = middle->next;
    middle->next = NULL;

    left = mergeSort(left);
    right = mergeSort(right);

    // Realizar a contagem de trocas aqui
    struct Node* mergedList = merge(left, right);

    // Atualizar as variáveis globais de trocas
    trocas += countNodes(left) + countNodes(right);

    return mergedList;
}

int main() {
    int N;
    printf("Digite o tamanho da lista: ");
    scanf("%d", &N);

    // Criação da lista com valores aleatórios
    struct Node* head = newNode(rand() % 1000);
    struct Node* current = head;
    for (int i = 1; i < N; i++) {
        current->next = newNode(rand() % 1000);
        current->next->prev = current;
        current = current->next;
    }

    // Redirecionar a saída padrão para um arquivo de saída
    // freopen("output.txt", "w", stdout);

    // Registrar o tempo de início
    clock_t start_time = clock();

    // Chame a função Merge Sort
    head = mergeSort(head);

    // Registrar o tempo de término
    clock_t end_time = clock();

    // Calcular o tempo de execução em segundos
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprimir a lista ordenada
    printList(head);

    // Imprima as estatísticas de comparações, trocas e tempo de execução no arquivo
    printf("Quantidade de comparacoes: %d\n", comparacoes);
    printf("Quantidade de trocas: %d\n", trocas);
    printf("Tempo de execucao: %f segundos\n", execution_time);
    printf("O tamanho da lista: %d", N);

    return 0;
}
