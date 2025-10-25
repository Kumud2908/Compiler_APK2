#include <stdio.h>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main() {
    int result = add(mul(2, 3), 5);
    printf("%d\n", result);
    return 0;
}
