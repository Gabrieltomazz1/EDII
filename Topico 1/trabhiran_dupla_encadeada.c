#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Função para criar um novo nó
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Função para liberar a memória alocada para a lista
void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* current = head;
        head = head->next;
        free(current);
    }
}

// Função para mesclar duas listas ordenadas em uma única lista ordenada
struct Node* merge(struct Node* left, struct Node* right, int* comparacoes, int* trocas) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    struct Node* result = NULL;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right, comparacoes, trocas);
        result->next->prev = result;
    } else {
        result = right;
        result->next = merge(left, right->next, comparacoes, trocas);
        result->next->prev = result;
    }

    (*comparacoes)++;

    return result;
}

// Função principal do Merge Sort para listas encadeadas
struct Node* mergeSort(struct Node* head, int* comparacoes, int* trocas) {
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

    left = mergeSort(left, comparacoes, trocas);
    right = mergeSort(right, comparacoes, trocas);

    struct Node* mergedList = merge(left, right, comparacoes, trocas);

    return mergedList;
}

// Função para criar uma lista com N valores aleatórios
struct Node* createRandomList(int N) {
    struct Node* head = newNode(rand() % 1000);
    struct Node* current = head;
    for (int i = 1; i < N; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = rand() % 1000;
        newNode->prev = current;
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}

int main() {
    int N;
    printf("Digite o tamanho da lista: ");
    scanf("%d", &N);

    // Registrar o tempo de início
    clock_t start_time = clock();

    int comparacoes = 0;
    int trocas = 0;

    // Criação da lista com valores aleatórios
    struct Node* head = createRandomList(N);

    // Chame a função Merge Sort
    head = mergeSort(head, &comparacoes, &trocas);

    // Registrar o tempo de término
    clock_t end_time = clock();

    // Calcular o tempo de execução em segundos
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprima as estatísticas de comparações, trocas e tempo de execução
    printf("Quantidade de comparacoes: %d\n", comparacoes);
    printf("Quantidade de trocas: %d\n", trocas);
    printf("Tempo de execucao: %f segundos\n", execution_time);
    printf("O tamanho da lista: %d\n", N);

    // Liberar a memória alocada para a lista
    freeList(head);

    return 0;
}
