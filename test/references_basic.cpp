#include <stdio.h>

void inc(int &x) {
    x = x + 1;
}

int main() {
    int a = 5;
    printf("Before: %d\n", a);
    inc(a);
    printf("After: %d\n", a);
    return 0;
}
