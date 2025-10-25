#include <stdio.h>

int main() {
    int a[3][3];
    int x = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = (i + j) * x;
            x++;
        }
    }

    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += a[i][j];
        }
    }

    printf("Sum = %d\n", sum);
    return 0;
}
