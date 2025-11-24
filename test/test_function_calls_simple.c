#include <stdio.h>

// Test 1: Simple addition
int add(int x, int y) {
    return x + y;
}

// Test 2: Simple subtraction
int sub(int x, int y) {
    return x - y;
}

// Test 3: Simple multiplication
int mul(int x, int y) {
    return x * y;
}

// Test 4: Function with no parameters
int getConstant() {
    return 100;
}

// Test 5: Function that returns parameter unchanged
int identity(int n) {
    return n;
}

// Test 6: Simple conditional
int absolute(int n) {
    if (n < 0) {
        return -n;
    }
    return n;
}

int main() {
    printf("Simple Function Tests\n");
    printf("=====================\n\n");
    
    // Basic calls
    printf("add(5, 3) = %d\n", add(5, 3));
    printf("sub(10, 4) = %d\n", sub(10, 4));
    printf("mul(6, 7) = %d\n", mul(6, 7));
    
    // No parameter function
    printf("getConstant() = %d\n", getConstant());
    
    // Identity function
    printf("identity(42) = %d\n", identity(42));
    
    // Conditional function
    printf("absolute(-15) = %d\n", absolute(-15));
    printf("absolute(20) = %d\n", absolute(20));
    
    // Nested calls - 2 levels
    printf("add(mul(2, 3), sub(10, 4)) = %d\n", add(mul(2, 3), sub(10, 4)));
    
    // Using return value in expression
    int result = add(10, 20) + mul(3, 4);
    printf("add(10, 20) + mul(3, 4) = %d\n", result);
    
    // Chain of operations
    int a = add(1, 2);
    int b = mul(a, 3);
    int c = sub(b, 1);
    printf("Chain: add(1,2)=3, mul(3,3)=9, sub(9,1) = %d\n", c);
    
    return 0;
}
