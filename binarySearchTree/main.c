/**
 * 1) Random 1000개의 숫자 생성 (중복 없음, Iteration마다 새로 생성)
 * 2) BST 생성
 * 3) Depth 계산, 생성 소요시간 계산 (millisecond)
 * 4) 1~3을 100회 반복, 평균 time, Depth와 max Depth, min Depth를출력
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 이진 탐색 트리의 노드 구조체
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 노드를 생성하여 반환하는 함수
TreeNode *create_node(int data) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 이진 탐색 트리에 노드를 추가하는 함수
void insert_node(TreeNode **root, int data) {

    if (*root == NULL) {
        *root = create_node(data);
        return;
    }

    if (*root == NULL) {
        *root = create_node(data);
    } else if (data < (*root)->data) {
        insert_node(&(*root)->left, data);
    } else {
        insert_node(&(*root)->right, data);
    }
}

// 이진 탐색 트리의 깊이를 계산하는 함수
int calc_depth(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }

    int left_depth = calc_depth(root->left);
    int right_depth = calc_depth(root->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    srand(time(NULL)); // 난수 생성기 초기화
    clock_t start_time, end_time;
    double elapsed_time;
    double avg_time = 0, avg_depth = 0;
    int max_depth = 0, min_depth = 10000;

    for (int i = 0; i < 100; i++) {
        TreeNode * root = NULL;
        int depth = 0;
        start_time = clock();
        for (int j = 0; j < 1000; j++) {
            int data = rand() % 10000;
            insert_node(&root, data);
        }
        depth = calc_depth(root);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
        avg_time += elapsed_time;
        avg_depth += depth;
        if (depth > max_depth) {
            max_depth = depth;
        }
        if (depth < min_depth) {
            min_depth = depth;
        }
        free_tree(root);
    }

    // 평균 소요시간과 평균 깊이 계산
    avg_time /= 100;
    avg_depth /= 100;

    // 결과 출력
    printf("Time avg : %.2f\n", avg_time);
    printf("Depth avg : %.2f\n", avg_depth);
    printf("Max: %d\n", max_depth);
    printf("Min: %d\n", min_depth);

    return 0;
}