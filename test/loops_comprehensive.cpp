#include <stdio.h>

int main() {
    printf("=== Basic For Loop ===\n");
    for (int i = 0; i < 5; i++) {
        printf("i = %d\n", i);
    }
    
    printf("\n=== Basic While Loop ===\n");
    int j = 0;
    while (j < 5) {
        printf("j = %d\n", j);
        j++;
    }
    
    printf("\n=== Basic Do-While Loop ===\n");
    int k = 0;
    do {
        printf("k = %d\n", k);
        k++;
    } while (k < 5);
    
    printf("\n=== For Loop with Decrement ===\n");
    for (int i = 5; i > 0; i--) {
        printf("i = %d\n", i);
    }
    
    printf("\n=== For Loop with Step 2 ===\n");
    for (int i = 0; i < 10; i += 2) {
        printf("i = %d\n", i);
    }
    
    printf("\n=== Nested For Loops ===\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("i=%d, j=%d, i*j=%d\n", i, j, i * j);
        }
    }
    
    printf("\n=== Loop with Break ===\n");
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            printf("Breaking at i = %d\n", i);
            break;
        }
        printf("i = %d\n", i);
    }
    
    printf("\n=== Loop with Continue ===\n");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;
        }
        printf("Odd: i = %d\n", i);
    }
    
    printf("\n=== While Loop with Break ===\n");
    int m = 0;
    while (1) {
        if (m >= 5) {
            break;
        }
        printf("m = %d\n", m);
        m++;
    }
    
    printf("\n=== Nested Loop with Break ===\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 2) {
                break;
            }
            printf("i=%d, j=%d\n", i, j);
        }
    }
    
    printf("\n=== Nested Loop with Continue ===\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j % 2 == 0) {
                continue;
            }
            printf("i=%d, j=%d\n", i, j);
        }
    }
    
    printf("\n=== Loop with Multiple Variables ===\n");
    for (int i = 0, j = 10; i < 5; i++, j--) {
        printf("i=%d, j=%d, sum=%d\n", i, j, i + j);
    }
    
    printf("\n=== Complex Loop Condition ===\n");
    for (int i = 0; i < 10 && i * i < 50; i++) {
        printf("i=%d, i*i=%d\n", i, i * i);
    }
    
    printf("\n=== Triple Nested Loop ===\n");
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            for (int k = 1; k <= 2; k++) {
                printf("i=%d, j=%d, k=%d\n", i, j, k);
            }
        }
    }
    
    printf("\n=== Do-While with Complex Condition ===\n");
    int n = 1;
    do {
        printf("n = %d\n", n);
        n *= 2;
    } while (n < 16);
    
    printf("\n=== Loop with Array ===\n");
    int arr[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("\n=== Reverse Loop ===\n");
    for (int i = 4; i >= 0; i--) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("\n=== While with Pre-increment ===\n");
    int p = 0;
    while (++p < 5) {
        printf("p = %d\n", p);
    }
    
    printf("\n=== While with Post-increment ===\n");
    int q = 0;
    while (q++ < 5) {
        printf("q = %d\n", q);
    }
    
    printf("\n=== Fibonacci with Loop ===\n");
    int f1 = 0, f2 = 1, fib;
    printf("Fibonacci: %d %d ", f1, f2);
    for (int i = 2; i < 10; i++) {
        fib = f1 + f2;
        printf("%d ", fib);
        f1 = f2;
        f2 = fib;
    }
    printf("\n");
    
    printf("\n=== Loop with Bitwise Operations ===\n");
    for (int i = 1; i < 32; i <<= 1) {
        printf("i = %d\n", i);
    }
    
    printf("\n=== Empty For Loop Body ===\n");
    int sum = 0;
    for (int i = 1; i <= 10; sum += i, i++);
    printf("Sum of 1 to 10 = %d\n", sum);
    
    printf("\n=== Loop with Compound Conditions ===\n");
    for (int i = 0, j = 10; i < j && i + j < 15; i++, j--) {
        printf("i=%d, j=%d, i+j=%d\n", i, j, i + j);
    }
    
    return 0;
}
