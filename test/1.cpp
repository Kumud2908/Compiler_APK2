#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    int (*func)(int, int); // declare function pointer

    func = add;
    printf("Add: %d\n", func(3, 4)); // 7

    func = multiply;
    printf("Multiply: %d\n", func(3, 4)); // 12

    return 0;
}
