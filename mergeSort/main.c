#include <stdio.h>
#include <stdlib.h> // rand를 사용하기 위한 헤더파일
#include <stdbool.h>
#include <time.h>

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l, sorted[1000];
    i = left;
    j = mid + 1;
    k = left;

    /* 분할 정렬된 list의 합병 */
    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
    }

    // 남아 있는 값들을 일괄 복사
    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
        }
    } else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
        }
    }

    // 배열 sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
    }
}

// 합병 정렬
void merge_sort(int list[], int left, int right) {
    int mid;

    if (left < right) {
        mid = (left + right) / 2; // 중간 위치를 계산하여 리스트를 균등 분할 - 분할(Divide)
        merge_sort(list, left, mid); // 앞쪽 부분 리스트 정렬 - 정복(Conquer)
        merge_sort(list, mid + 1, right); // 뒤쪽 부분 리스트 정렬 = 정복(Conquer)
        merge(list, left, mid, right); // 정렬된 2개의 부분 배열을 합병하는 과정 - 결합
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

    FILE *fp_input, *fp_m_output, *fp_m_match;

    // 난수 초기화
    srand(time(NULL));

    // 난수 생성 및 중복값 제거
    int random[1000];
    bool is_duplicate;

    for (int i = 0; i < 1000; i++) {
        do {
            random[i] = rand() % 1000;
            is_duplicate = false;
            for (int j = 0; j < i; j++) {
                if (random[j] == random[i]) {
                    is_duplicate = true;
                    break;
                }
            }
        } while (is_duplicate);
    }

    // input.txt 생성
    fp_input = fopen("input.txt", "w");
    for (i = 0; i < 1000; i++) {
        fprintf(fp_input, "%d ", random[i]); // txt 파일에 난수 입력
    }
    fclose(fp_input);

    // input.txt 읽기
    int arr[1000];
    fp_input = fopen("input.txt", "r");
    // input.txt 값 배열에 저장
    for (i = 0; i < 1000; i++) {
        fscanf(fp_input, "%d", &arr[i]);
    }
    fclose(fp_input);

    // 합병 정렬로 배열 정렬
    int m_sort[1000];
    for (i = 0; i < 1000; i++) {
        m_sort[i] = arr[i];
    }
    merge_sort(m_sort, 0, 1000 - 1);

    // output.txt 파일 쓰기
    fp_m_output = fopen("output.txt", "w");
    for (i = 0; i < 1000; i++) {
        fprintf(fp_m_output, "%d ", m_sort[i]);
    }
    fclose(fp_m_output);

    // match.txt 생성
    fp_m_match = fopen("match.txt", "w");
    int match = countMatch(arr, m_sort);
    fprintf(fp_m_match, "같은 위치에 존재하는 숫자의 개수 : %d\n", match);
    for (i = 0; i < 1000; i++) {
        if (arr[i] == m_sort[i]) {
            fprintf(fp_m_match, "%d ", i);
        }
    }
    fclose(fp_m_match);

    return 0;
}