#include <stdio.h>

int main() {
    int x[2][2] = {{1, 2}, {3, 4}};
    int y[2][2] = {{5, 6}, {7, 8}};
    int z[2][2];
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            z[i][j] = x[i][j] + y[i][j];
        }
    }
    
    printf("Result:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", z[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
