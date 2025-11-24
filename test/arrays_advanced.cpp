#include <stdio.h>

// Test comprehensive array operations
int main() {
    // Test 1: Basic 1D array
    printf("Test 1: Basic array\n");
    int a[5] = {1, 2, 3, 4, 5};
    int i;
    
    printf("Initial: ");
    for (i = 0; i < 5; i = i + 1) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    // Test 2: Modify elements
    printf("\nTest 2: Modify elements\n");
    a[0] = 10;
    a[2] = 30;
    a[4] = 50;
    
    printf("Modified: ");
    for (i = 0; i < 5; i = i + 1) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    // Test 3: Array operations
    printf("\nTest 3: Array sum\n");
    int sum = 0;
    for (i = 0; i < 5; i = i + 1) {
        sum = sum + a[i];
    }
    printf("Sum = %d\n", sum);
    
    // Test 4: Find max
    printf("\nTest 4: Find max\n");
    int max = a[0];
    for (i = 1; i < 5; i = i + 1) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    printf("Max = %d\n", max);
    
    // Test 5: 2D array
    printf("\nTest 5: 2D array\n");
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    printf("Matrix:\n");
    int r;
    int c;
    for (r = 0; r < 2; r = r + 1) {
        for (c = 0; c < 3; c = c + 1) {
            printf("%d ", mat[r][c]);
        }
        printf("\n");
    }
    
    // Test 6: Modify 2D array
    printf("\nTest 6: Modify 2D\n");
    mat[0][1] = 20;
    mat[1][2] = 60;
    
    printf("Modified matrix:\n");
    for (r = 0; r < 2; r = r + 1) {
        for (c = 0; c < 3; c = c + 1) {
            printf("%d ", mat[r][c]);
        }
        printf("\n");
    }
    
    // Test 7: Reverse print
    printf("\nTest 7: Reverse print\n");
    for (i = 4; i >= 0; i = i - 1) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
