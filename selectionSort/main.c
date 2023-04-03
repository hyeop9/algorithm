#include <stdio.h>
#include <stdlib.h> // rand를 사용하기 위한 헤더파일

// Selection sort
void SelectionSort(int arr[], int len) {
    int min_idx, tmp;
    for (int i = 0; i < len - 1; ++i) {
        min_idx = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        // 임시 변수 tmp를 통해 정렬을 위한 swap을 진행
        tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

// countMatch 함수
int countMatch(int A[], int B[]) {
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        if (A[i] == B[i]) {
            count++;
        }
    }
    return count;
}

int main() {

    FILE *fp_input, *fp_s_output, *fp_s_match;

    // input.txt 생성
    int random;
    fp_input = fopen("input.txt", "w");
    // 난수 생성
    for (int i = 0; i < 1000; i++) {
        random = rand() % 1000;
        fprintf(fp_input, "%d ", random); // txt 파일에 난수 입력
    }
    fclose(fp_input);

    // input.txt 읽기
    int arr[1000];
    fp_input = fopen("input.txt", "r");
    // input.txt 값 배열에 저장
    for (int i = 0; i < 1000; i++) {
        fscanf(fp_input, "%d", &arr[i]);
    }
    fclose(fp_input);

    // 선택 정렬로 배열 정렬
    int s_sort[1000];
    for (int i = 0; i < 1000; i++) {
        s_sort[i] = arr[i];
    }
    SelectionSort(s_sort, 1000);

    // output.txt 파일 쓰기
    fp_s_output = fopen("output.txt", "w");
    for (int i = 0; i < 1000; i++) {
        fprintf(fp_s_output, "%d ", s_sort[i]);
    }
    fclose(fp_s_output);

    // match.txt 생성
    fp_s_match = fopen("match.txt", "w");
    int match = countMatch(arr, s_sort);
    fprintf(fp_s_match, "같은 위치에 존재하는 숫자의 개수 : %d\n", match);
    for (int i = 0; i < 1000; i++) {
        if (arr[i] == s_sort[i]) {
            fprintf(fp_s_match, "%d ", i);
        }
    }
    fclose(fp_s_match);

    return 0;
}