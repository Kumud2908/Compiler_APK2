#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data d;

    d.i = 65;
    printf("i = %d\n", d.i);

    d.c = 'A';
    printf("c = %c, i = %d\n", d.c, d.i);

    d.f = 3.14;
    printf("f = %.2f, i = %d\n", d.f, d.i);

    return 0;
}
