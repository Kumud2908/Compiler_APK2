#include <stdio.h>

int main() {
    int x = 0;

    // until (x >= 5)
    do {
        printf("x = %d\n", x);
        x++;
    } while (!(x >= 5));

    return 0;
}
