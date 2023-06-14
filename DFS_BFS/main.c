#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 트리의 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* children[3]; // 최대 3개의 자식 노드를 가질 수 있음
} Node;

// 새로운 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    int i;
    for (i = 0; i < 3; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// 트리를 랜덤하게 생성하는 함수
Node* createRandomTree(int height) {
    if (height == 0) {
        return NULL;
    }
    Node* root = createNode(rand() % 100); // 0부터 99 사이의 랜덤한 값을 가진 루트 노드 생성

    int i;
    for (i = 0; i < 3; i++) {
        root->children[i] = createRandomTree(height - 1); // 자식 노드 생성
    }

    return root;
}

// DFS 탐색 함수
void dfs(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d->", node->data); // 현재 노드의 데이터 출력

    int i;
    for (i = 0; i < 3; i++) {
        dfs(node->children[i]); // 자식 노드로 재귀 호출
    }
}

// BFS 탐색 함수
void bfs(Node* root) {
    if (root == NULL) {
        return;
    }

    // 큐를 사용하여 BFS 구현
    Node* queue[1000]; // 큐
    int front = 0; // 큐의 시작 인덱스
    int rear = 0; // 큐의 끝 인덱스

    queue[rear++] = root; // 루트 노드를 큐에 삽입

    while (front < rear) {
        Node* currentNode = queue[front++]; // 큐에서 노드를 하나 꺼냄
        printf("%d->", currentNode->data); // 현재 노드의 데이터 출력

        int i;
        for (i = 0; i < 3; i++) {
            if (currentNode->children[i] != NULL) {
                queue[rear++] = currentNode->children[i]; // 자식 노드를 큐에 삽입
            }
        }
    }
}

int main() {
    int height;

    printf("Input : ");
    scanf("%d", &height);

    srand(time(NULL)); // 랜덤 시드 초기화

    // 랜덤한 트리 생성
    Node* root = createRandomTree(height);

    // DFS 탐색 및 수행 시간 측정
    clock_t startDFS = clock();
    dfs(root);
    clock_t endDFS = clock();
    printf("\n");

    // BFS 탐색 및 수행 시간 측정
    clock_t startBFS = clock();
    bfs(root);
    clock_t endBFS = clock();
    printf("\n");

    // 수행 시간 계산
    double timeDFS = (double)(endDFS - startDFS) * 1000.0 / CLOCKS_PER_SEC;
    double timeBFS = (double)(endBFS - startBFS) * 1000.0 / CLOCKS_PER_SEC;

    // 수행 시간 출력
    printf("DFS: %.3f msec\n", timeDFS);
    printf("BFS: %.3f msec\n", timeBFS);

    return 0;
}