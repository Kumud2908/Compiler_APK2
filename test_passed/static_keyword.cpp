#include <stdio.h>

void test() {
    static int x;  // Should default to 0
    x = x + 5;
    printf("%d\n", x);
}

int main() {
    test();  // Should print: 5
    test();  // Should print: 10
    test();  // Should print: 15
    return 0;
}