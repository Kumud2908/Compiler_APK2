// Complex nested loops with break and continue
#include <stdio.h>

int main() {
    int matrix[3][3];
    int sum = 0;
    
    // Initialize matrix with nested loops
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = i * 3 + j + 1;
        }
    }
    
    // Complex nested loop with break/continue
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == 5) {
                continue;  // Skip 5
            }
            if (matrix[i][j] > 7) {
                break;  // Stop at values > 7
            }
            sum += matrix[i][j];
        }
    }
    
    printf("Sum: %d\n", sum);  // Should be 1+2+3+4+6+7 = 23
    return 0;
}
