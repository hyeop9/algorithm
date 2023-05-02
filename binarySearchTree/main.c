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

// 노드를 삽입하는 함수
void insert_node(TreeNode **root, int data) {
    if (*root == NULL) {
        *root = create_node(data);
    } else if (data < (*root)->data) {
        insert_node(&((*root)->left), data);
    } else if (data > (*root)->data) {
        insert_node(&((*root)->right), data);
    }
}

// 이진 탐색 트리의 깊이를 계산하는 함수
int calc_depth(TreeNode *root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_depth = calc_depth(root->left);
        int right_depth = calc_depth(root->right);
        return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
    }
}


int main() {
    int num_iterations = 100;
    int num_numbers = 1000;

    // 랜덤 숫자 배열 생성
    int *numbers = (int *) malloc(sizeof(int) * num_numbers);
    srand(time(NULL));
    for (int i = 0; i < num_numbers; i++) {
        numbers[i] = rand() % (num_numbers * 10) + 1;
        for (int j = 0; j < i; j++) {
            if (numbers[i] == numbers[j]) {
                i--;
                break;
            }
        }
    }

    // 반복 수행
    double total_time = 0.0;
    int total_depth = 0;
    int max_depth = 0, min_depth = 1000;
    for (int i = 0; i < num_iterations; i++) {
        // 이진 탐색 트리 생성
        TreeNode *root = NULL;
        clock_t start_time = clock();

        for (int j = 0; j < num_numbers; j++) {
            insert_node(&root, numbers[j]);
        }

        clock_t end_time = clock();
        double time_elapsed = (double) (end_time - start_time) / CLOCKS_PER_SEC;

        // 이진 탐색 트리의 깊이 계산
        int depth = calc_depth(root);

        // 최대 깊이와 최소 깊이 업데이트
        if (depth > max_depth) {
            max_depth = depth;
        }
        if (depth < min_depth) {
            min_depth = depth;
        }

        // 총 소요시간과 총 깊이 업데이트
        total_time += time_elapsed;
        total_depth += depth;
    }

    // 평균 시간, 평균 Depth, 최대 Depth, 최소 Depth 출력
    double avg_time = total_time / num_iterations;
    double avg_depth = (double) total_depth / num_iterations;
    printf("Time Avg : %.2f\n", avg_time);
    printf("Depth Avg : %.2f\n", avg_depth);
    printf("Max: %d\n", max_depth);
    printf("Min: %d\n", min_depth);

    free(numbers);
    return 0;
}