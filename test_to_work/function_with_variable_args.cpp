#include <stdio.h>
#include <stdarg.h>

// Function with variable arguments
int sum(int count, ...) {
    int total = 0;
    va_list args;           // Initialize argument list
    va_start(args, count);  // Start from last known parameter

    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int); // Retrieve next argument
        total += num;
    }

    va_end(args); // Clean up
    return total;
}

int main() {
    int s = sum(4, 10, 20, 30, 40);
    printf("Sum = %d\n", s);

    return 0;
}
