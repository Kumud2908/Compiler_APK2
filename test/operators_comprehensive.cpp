// Complex arithmetic and bitwise operations
#include <stdio.h>

int main() {
    int a = 15;  // 1111 in binary
    int b = 10;  // 1010 in binary
    
    // Arithmetic operations
    printf("Arithmetic:\n");
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d\n", a, b, a / b);
    printf("%d %% %d = %d\n", a, b, a % b);
    
    // Bitwise operations
    printf("\nBitwise:\n");
    printf("%d & %d = %d\n", a, b, a & b);   // AND: 1010 = 10
    printf("%d | %d = %d\n", a, b, a | b);   // OR:  1111 = 15
    printf("%d ^ %d = %d\n", a, b, a ^ b);   // XOR: 0101 = 5
    printf("~%d = %d\n", a, ~a);
    
    // Shift operations
    printf("\nShift:\n");
    printf("%d << 2 = %d\n", a, a << 2);     // 60
    printf("%d >> 2 = %d\n", a, a >> 2);     // 3
    
    // Complex expression
    int result = ((a + b) * 2) - (a / b) + (a % b);
    printf("\nComplex: ((15+10)*2) - (15/10) + (15%%10) = %d\n", result);
    
    // Comparison and logical
    printf("\nComparison:\n");
    printf("%d > %d: %d\n", a, b, a > b);
    printf("%d < %d: %d\n", a, b, a < b);
    printf("%d == %d: %d\n", a, b, a == b);
    printf("%d != %d: %d\n", a, b, a != b);
    
    return 0;
}
