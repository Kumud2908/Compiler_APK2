#include <stdio.h>

// Typedef for a new name for int
typedef int myInt;

// Typedef for a struct
typedef struct {
    int x;
    int y;
} Point;

// Typedef for pointer type
typedef char* String;

int main() {
    myInt a = 10;        // Using typedef alias for int
    Point p1 = {1, 2};   // Using typedef alias for struct
    String s = "Hello";  // Using typedef alias for char*

    printf("a = %d\n", a);
    printf("Point: (%d, %d)\n", p1.x, p1.y);
    printf("String: %s\n", s);

    return 0;
}
