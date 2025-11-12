#include <stdio.h>

// Function declarations
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Declare a function pointer
    int (*operation)(int, int);

    int x = 10, y = 5;

    // Assign different functions to the pointer and call them
    operation = add;
    printf("Addition: %d + %d = %d\n", x, y, operation(x, y));

    operation = subtract;
    printf("Subtraction: %d - %d = %d\n", x, y, operation(x, y));

    operation = multiply;
    printf("Multiplication: %d * %d = %d\n", x, y, operation(x, y));

    return 0;
}
