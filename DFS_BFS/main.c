#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 트리의 노드 구조체
typedef struct Node {
    int data;
    struct Node** children;
    int numChildren;
} Node;

// 트리의 노드 생성
Node* createNode(int data, int numChildren) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->numChildren = numChildren;
    node->children = (Node**)malloc(numChildren * sizeof(Node*));
    return node;
}

// 트리 생성
Node* createTree(int height) {
    if (height <= 0)
        return NULL;

    Node* root = createNode(0, rand() % 3 + 1);

    for (int i = 0; i < root->numChildren; i++) {
        root->children[i] = createTree(height - 1);
    }

    return root;
}

// DFS 탐색
void DFS(Node* node) {
    if (node == NULL)
        return;

    printf("%d->", node->data);

    for (int i = 0; i < node->numChildren; i++) {
        DFS(node->children[i]);
    }
}

// BFS 탐색
void BFS(Node* root) {
    Node* queue[1000];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%d->", current->data);

        for (int i = 0; i < current->numChildren; i++) {
            queue[rear++] = current->children[i];
        }
    }
}

// 트리 메모리 해제
void freeTree(Node* node) {
    if (node == NULL)
        return;

    for (int i = 0; i < node->numChildren; i++) {
        freeTree(node->children[i]);
    }

    free(node->children);
    free(node);
}


int main() {
    int height;
    struct timespec start, end;
    double DFSTime, BFSTime;

    printf("Input: ");
    scanf("%d", &height);

    srand(time(0));
    Node* root = createTree(height);

    // DFS 탐색 및 수행 시간 측정
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("DFS: ");
    DFS(root);
    clock_gettime(CLOCK_MONOTONIC, &end);
    DFSTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    // BFS 탐색 및 수행 시간 측정
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("BFS: ");
    BFS(root);
    clock_gettime(CLOCK_MONOTONIC, &end);
    BFSTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("DFS: %.3lfsec\n", DFSTime);
    printf("BFS: %.3lfsec\n", BFSTime);

    // 트리 메모리 해제
    freeTree(root);

    return 0;
}
