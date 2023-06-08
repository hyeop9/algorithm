#include <stdio.h>
#include <time.h>

// 재귀 함수
unsigned long long recursiveFibonacci(int n)
{
    if (n <= 1)
        return n;
    else
        return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
}

// 동적 프로그래밍
unsigned long long dynamicFibonacci(int n)
{
    unsigned long long fib[n + 1];
    int i;

    fib[0] = 0;
    fib[1] = 1;

    for (i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    return fib[n];
}

int main()
{
    int n;
    clock_t start, end;
    double recursiveTime, dynamicTime;
    unsigned long long recursiveResult, dynamicResult;

    printf("Input: ");
    scanf("%d", &n);

    // 재귀 함수 실행 및 수행 시간 측정
    start = clock();
    recursiveResult = recursiveFibonacci(n);
    end = clock();
    recursiveTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    // 동적 프로그래밍 실행 및 수행 시간 측정
    start = clock();
    dynamicResult = dynamicFibonacci(n);
    end = clock();
    dynamicTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    // 결과 출력
    printf("Recursive: %llu / %.3lfsec\n", recursiveResult, recursiveTime);
    printf("Dynamic: %llu / %.3lfsec\n", dynamicResult, dynamicTime);

    return 0;
}
