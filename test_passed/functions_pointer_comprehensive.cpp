// Complex function pointer operations
#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

// Function that takes function pointer as parameter
int apply_operation(int x, int y, int (*op)(int, int)) {
    return op(x, y);
}

int main() {
    int (*operations[4])(int, int);
    operations[0] = add;
    operations[1] = subtract;
    operations[2] = multiply;
    operations[3] = divide;
    
    int a = 20, b = 4;
    
    printf("Operations on %d and %d:\n", a, b);
    printf("Add: %d\n", operations[0](a, b));       // 24
    printf("Subtract: %d\n", operations[1](a, b));  // 16
    printf("Multiply: %d\n", operations[2](a, b));  // 80
    printf("Divide: %d\n", operations[3](a, b));    // 5
    
    // Using function that takes function pointer
    printf("Using apply_operation:\n");
    printf("Result: %d\n", apply_operation(10, 5, add));      // 15
    printf("Result: %d\n", apply_operation(10, 5, multiply)); // 50
    
    return 0;
}
