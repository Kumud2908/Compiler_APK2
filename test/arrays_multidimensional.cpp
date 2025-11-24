#include <stdio.h>

int main() {
    printf("=== Test 1: Basic 2D Array Access ===\n");
    int matrix[2][2] = {{1, 2}, {3, 4}};
    printf("matrix[0][0] = %d\n", matrix[0][0]);
    printf("matrix[0][1] = %d\n", matrix[0][1]);
    printf("matrix[1][0] = %d\n", matrix[1][0]);
    printf("matrix[1][1] = %d\n", matrix[1][1]);
    
    printf("\n=== Test 2: 3x3 Matrix Operations ===\n");
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    printf("Original Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Test 3: Matrix Transpose ===\n");
    int b[3][3];
    
    // Transpose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b[j][i] = a[i][j];
        }
    }
    
    printf("Transposed Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Test 4: Sum of All Elements ===\n");
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum = sum + a[i][j];
        }
    }
    printf("Total sum: %d\n", sum);
    
    printf("\n=== Test 5: Row Sums ===\n");
    for (int i = 0; i < 3; i++) {
        int row_sum = 0;
        for (int j = 0; j < 3; j++) {
            row_sum = row_sum + a[i][j];
        }
        printf("Row %d sum: %d\n", i, row_sum);
    }
    
    printf("\n=== Test 6: Column Sums ===\n");
    for (int j = 0; j < 3; j++) {
        int col_sum = 0;
        for (int i = 0; i < 3; i++) {
            col_sum = col_sum + a[i][j];
        }
        printf("Column %d sum: %d\n", j, col_sum);
    }
    
    printf("\n=== Test 7: Diagonal Elements ===\n");
    printf("Main diagonal: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", a[i][i]);
    }
    printf("\n");
    
    printf("Anti-diagonal: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", a[i][2 - i]);
    }
    printf("\n");
    
    printf("\n=== Test 8: Array Copy ===\n");
    int c[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[i][j] = a[i][j];
        }
    }
    printf("Copied array:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Test 11: Scalar Multiplication ===\n");
    int scalar = 2;
    printf("Multiply by %d:\n", scalar);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i][j] * scalar);
        }
        printf("\n");
    }
    
    printf("\n=== Test 10: Pattern Generation ===\n");
    int pattern[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pattern[i][j] = i + j;
        }
    }
    printf("Pattern (i+j):\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", pattern[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Test 14: Counter Pattern ===\n");
    int counter[3][3];
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            counter[i][j] = count;
            count = count + 1;
        }
    }
    printf("Counter matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", counter[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Test 15: Boundary Elements ===\n");
    printf("Top row: ");
    for (int j = 0; j < 3; j++) {
        printf("%d ", a[0][j]);
    }
    printf("\n");
    
    printf("Bottom row: ");
    for (int j = 0; j < 3; j++) {
        printf("%d ", a[2][j]);
    }
    printf("\n");
    
    printf("Left column: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", a[i][0]);
    }
    printf("\n");
    
    printf("Right column: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", a[i][2]);
    }
    printf("\n");
    
    printf("\n=== All 10 Tests Completed Successfully! ===\n");
    
    return 0;
}