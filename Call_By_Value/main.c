#include <stdio.h>

void sub(int v);

int main() {
    int i = 100;
    sub(i);
    printf("i = %d\n", i);
    return 0;
}

void sub(int v) {
    v = 200;
}