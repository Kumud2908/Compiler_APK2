#include <stdio.h>

typedef int myInt;

typedef struct {
    int x;
    int y;
} Point;

typedef char* String;

int main() {
    myInt a = 10;
    Point p1 = {1, 2};
    String s = "Hello";

    printf("a = %d\n", a);
    printf("Point: (%d, %d)\n", p1.x, p1.y);
    printf("String: %s\n", s);

    return 0;
}
