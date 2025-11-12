#include <stdio.h>

int main() {
    int a = 10, b = 3;
    float x = 2.5, y = 4.0;
    
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int quot = a / b;
    int rem  = a % b;

    float fsum = x + y;
    float mix  = a + x;   // mixed int-float operation
    float divf = y / b;

    // Print integer operations
    printf("Integer Operations:\n");
    printf("Sum = %d\n", sum);
    printf("Difference = %d\n", diff);
    printf("Product = %d\n", prod);
    printf("Quotient = %d\n", quot);
    printf("Remainder = %d\n\n", rem);

    // Print float operations
    printf("Float Operations:\n");
    printf("Float Sum = %.2f\n", fsum);
    printf("Mixed (a + x) = %.2f\n", mix);
    printf("Float Division (y / b) = %.2f\n", divf);

    return 0;
}
