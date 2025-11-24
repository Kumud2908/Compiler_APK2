#include <stdio.h>

// Basic arithmetic functions
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int sub(int a, int b) { return a - b; }
int divide(int a, int b) { 
    if (b != 0) return a / b;
    return 0;
}

// Function with no parameters
int getConstant() { return 42; }

// Function with single parameter
int square(int x) { return x * x; }
int triple(int x) { return x * 3; }

// Recursive function - factorial
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Function that calls multiple functions
int compute(int x, int y) {
    int sum = add(x, y);
    int product = mul(sum, 2);
    return sub(product, 1);
}

// Conditional function
int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int main() {
    printf("=== Function Call Tests ===\n\n");
    
    // Test 1: Original nested call
    int result = add(mul(2, 3), 5);
    printf("Test 1 - add(mul(2, 3), 5): %d\n", result);
    
    // Test 2: Three-level nesting
    printf("Test 2 - add(mul(2, 3), sub(10, 5)): %d\n", 
           add(mul(2, 3), sub(10, 5)));
    
    // Test 3: Function with no parameters
    printf("Test 3 - getConstant(): %d\n", getConstant());
    
    // Test 4: Single parameter function
    printf("Test 4 - square(7): %d\n", square(7));
    printf("Test 5 - triple(5): %d\n", triple(5));
    
    // Test 6: Recursive function
    printf("Test 6 - factorial(5): %d\n", factorial(5));
    printf("Test 7 - factorial(6): %d\n", factorial(6));
    
    // Test 7: Multiple operations
    printf("Test 8 - mul(add(3, 4), sub(10, 5)): %d\n", 
           mul(add(3, 4), sub(10, 5)));
    
    // Test 8: Four-level nesting
    printf("Test 9 - add(mul(square(2), 3), divide(20, 4)): %d\n",
           add(mul(square(2), 3), divide(20, 4)));
    
    // Test 9: Function calling multiple functions
    printf("Test 10 - compute(5, 10): %d\n", compute(5, 10));
    
    // Test 10: Conditional functions
    printf("Test 11 - max(15, 23): %d\n", max(15, 23));
    printf("Test 12 - min(15, 23): %d\n", min(15, 23));
    
    // Test 11: Nested max/min
    printf("Test 13 - max(min(10, 20), max(5, 15)): %d\n",
           max(min(10, 20), max(5, 15)));
    
    // Test 12: Complex expression
    int a = add(5, 3);
    int b = mul(a, 2);
    int c = sub(b, 4);
    printf("Test 14 - Chain: a=%d, b=%d, c=%d\n", a, b, c);
    
    // Test 13: Factorial in expression
    printf("Test 15 - add(factorial(4), square(5)): %d\n",
           add(factorial(4), square(5)));
    
    // Test 14: Division in nested calls
    printf("Test 16 - mul(divide(100, 5), add(2, 3)): %d\n",
           mul(divide(100, 5), add(2, 3)));
    
    // Test 15: All operations combined
    printf("Test 17 - sub(mul(add(2, 3), divide(20, 4)), square(2)): %d\n",
           sub(mul(add(2, 3), divide(20, 4)), square(2)));
    
    printf("\n=== All tests completed ===\n");
    return 0;
}
