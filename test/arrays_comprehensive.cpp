// Complex array operations - matrix manipulation
#include <stdio.h>

int main() {
    int matrix1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int transposed[3][3];
    int product[3][3];
    
    printf("Matrix 1:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatrix 2:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    
    // Transpose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transposed[j][i] = matrix1[i][j];
        }
    }
    
    printf("\nTransposed Matrix 1:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
    
    // Matrix multiplication
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            product[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                product[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    printf("\nMatrix 1 * Matrix 2:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", product[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
