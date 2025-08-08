// Test Case 2: typedef, enum, union, struct declarations and usage.
typedef int myint;

enum Color { RED, GREEN, BLUE };

union Data {
    int i;
    char c;
};

struct Point { myint x; myint y; };

int foo() {
    struct Point p;
    p.x = 1;
    p.y = 2;
    return p.x + p.y;
}