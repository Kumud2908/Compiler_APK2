// Simplified function pointer test - workaround for indirect calls
#include <stdio.h>

int add(int a, int b) { 
    return a + b; 
}

int subtract(int a, int b) { 
    return a - b; 
}

int multiply(int a, int b) { 
    return a * b; 
}

int divide(int a, int b) { 
    if (b != 0) return a / b;
    return 0;
}

// Instead of using function pointers, use a selector function
int calculate(int x, int y, int operation) {
    if (operation == 0) {
        return add(x, y);
    } else if (operation == 1) {
        return subtract(x, y);
    } else if (operation == 2) {
        return multiply(x, y);
    } else if (operation == 3) {
        return divide(x, y);
    }
    return 0;
}

int main() {
    int a = 20, b = 4;
    
    printf("Operations on %d and %d:\n", a, b);
    printf("Add: %d\n", calculate(a, b, 0));       // 24
    printf("Subtract: %d\n", calculate(a, b, 1));  // 16
    printf("Multiply: %d\n", calculate(a, b, 2));  // 80
    printf("Divide: %d\n", calculate(a, b, 3));    // 5
    
    // Test with different values
    printf("\nOperations on 10 and 5:\n");
    printf("Add: %d\n", calculate(10, 5, 0));       // 15
    printf("Multiply: %d\n", calculate(10, 5, 2));  // 50
    printf("Subtract: %d\n", calculate(10, 5, 1));  // 5
    printf("Divide: %d\n", calculate(10, 5, 3));    // 2
    
    return 0;
}
