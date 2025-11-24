// Complex control flow with goto
#include <stdio.h>

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int target = 5;
    int found = 0;
    int row = -1, col = -1;
    
    // Search in matrix using goto
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == target) {
                row = i;
                col = j;
                found = 1;
                goto search_done;
            }
        }
    }
    
search_done:
    if (found) {
        printf("Found %d at position (%d, %d)\n", target, row, col);
    } else {
        printf("Not found\n");
    }
    
    // Complex goto with cleanup
    int error = 0;
    int x = 10;
    
    if (x < 0) {
        error = 1;
        goto cleanup;
    }
    
    printf("Processing x = %d\n", x);
    x = x * 2;
    
cleanup:
    if (error) {
        printf("Error occurred\n");
    } else {
        printf("Success: x = %d\n", x);
    }
    
    return 0;
}
