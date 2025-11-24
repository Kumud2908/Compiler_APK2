#include <stdio.h>

// Basic function - no parameters
int getValue() {
    return 42;
}

// Basic function - single parameter
int square(int x) {
    return x * x;
}

// Basic function - multiple parameters
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
    if (b != 0) {
        return a / b;
    }
    return 0;
}

// Recursive function - factorial
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Recursive function - fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Function that calls multiple other functions
int compute(int a, int b, int c) {
    int sum = add(a, b);
    int prod = multiply(sum, c);
    int diff = subtract(prod, a);
    return diff;
}

// Nested function calls - deep nesting
int complexCalc(int x, int y) {
    return add(multiply(x, y), subtract(square(x), divide(y, 2)));
}

// Function with conditional logic and function calls
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

// Function using loops and function calls
int sumUpTo(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = add(sum, i);
    }
    return sum;
}

int main() {
    printf("=== BASIC FUNCTION CALLS ===\n");
    
    // Test 1: No parameters
    printf("getValue(): %d\n", getValue());
    
    // Test 2: Single parameter
    printf("square(5): %d\n", square(5));
    
    // Test 3: Multiple parameters
    printf("add(10, 20): %d\n", add(10, 20));
    printf("subtract(50, 15): %d\n", subtract(50, 15));
    printf("multiply(7, 8): %d\n", multiply(7, 8));
    printf("divide(100, 4): %d\n", divide(100, 4));
    
    printf("\n=== NESTED FUNCTION CALLS ===\n");
    
    // Test 4: Function as argument
    printf("add(square(3), multiply(2, 5)): %d\n", add(square(3), multiply(2, 5)));
    
    // Test 5: Deep nesting
    printf("complexCalc(5, 10): %d\n", complexCalc(5, 10));
    
    // Test 6: Multiple levels of nesting
    printf("multiply(add(2, 3), subtract(10, 5)): %d\n", 
           multiply(add(2, 3), subtract(10, 5)));
    
    printf("\n=== RECURSIVE FUNCTIONS ===\n");
    
    // Test 7: Factorial
    printf("factorial(5): %d\n", factorial(5));
    printf("factorial(6): %d\n", factorial(6));
    
    // Test 8: Fibonacci
    printf("fibonacci(7): %d\n", fibonacci(7));
    printf("fibonacci(10): %d\n", fibonacci(10));
    
    printf("\n=== COMPLEX SCENARIOS ===\n");
    
    // Test 9: Function calling multiple functions
    printf("compute(5, 10, 3): %d\n", compute(5, 10, 3));
    
    // Test 10: Conditional function calls
    printf("max(15, 23): %d\n", max(15, 23));
    printf("min(15, 23): %d\n", min(15, 23));
    
    // Test 11: Loop with function calls
    printf("sumUpTo(10): %d\n", sumUpTo(10));
    
    // Test 12: Complex expression with multiple function calls
    int result = add(
        multiply(square(2), factorial(3)),
        subtract(divide(100, 5), fibonacci(5))
    );
    printf("Complex expression result: %d\n", result);
    
    // Test 13: Chained function calls
    printf("max(min(10, 20), max(5, 15)): %d\n", 
           max(min(10, 20), max(5, 15)));
    
    return 0;
}
