// Test Case 3: Function call with variable arguments, typedef usage

#include <stdio.h>
#include <stdarg.h>

typedef unsigned int uint;

void printNumbers(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        printf("%d ", num);
    }
    va_end(args);
    printf("\n");
}

int main() {
    uint x = 100;
    printf("Unsigned integer typedef: %u\n", x);
    printNumbers(4, 10, 20, 30, 40);
    return 0;
}