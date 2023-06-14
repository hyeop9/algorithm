#include <stdio.h>
#include <time.h>

// 재귀 함수를 사용하여 피보나치 수 계산
long long fibonacciRecursive(int n) {
    // 기저 조건: n이 0 또는 1일 때는 n을 반환
    if (n == 0 || n == 1) {
        return n;
    }

    // 피보나치 수 계산
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// 동적 프로그래밍을 사용하여 피보나치 수 계산
long long fibonacciDynamic(int n) {
    // 피보나치 수를 저장할 배열
    long long fib[n + 1];
    int i;

    // 초기 값 설정
    fib[0] = 0;  // 첫 번째 피보나치 수
    fib[1] = 1;  // 두 번째 피보나치 수

    // 피보나치 수 계산
    for (i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];  // 현재 항은 이전 두 항의 합으로 계산됨
    }

    // n번째 피보나치 수 반환
    return fib[n];
}

int main() {
    int n;

    printf("Input: ");
    scanf("%d", &n);

    // 재귀 함수를 사용하여 피보나치 수 계산 및 수행 시간 측정
    clock_t startRecursive = clock();
    long long resultRecursive = fibonacciRecursive(n);
    clock_t endRecursive = clock();

    // 동적 프로그래밍을 사용하여 피보나치 수 계산 및 수행 시간 측정
    clock_t startDynamic = clock();
    long long resultDynamic = fibonacciDynamic(n);
    clock_t endDynamic = clock();

    // 수행 시간 계산
    double timeRecursive = (double)(endRecursive - startRecursive) * 1000.0 / CLOCKS_PER_SEC;
    double timeDynamic = (double)(endDynamic - startDynamic) * 1000.0 / CLOCKS_PER_SEC;

    // 결과 출력
    printf("Recursive: %lld / %.3f msec\n", resultRecursive, timeRecursive);
    printf("Dynamic: %lld / %.3f msec\n", resultDynamic, timeDynamic);

    return 0;
}
