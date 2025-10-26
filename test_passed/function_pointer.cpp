// #include <stdio.h>

// int add(int a, int b) {
//     return a + b;
// }

// int main() {
//     int (*fptr)(int, int);
//     fptr = add;

//     int result = fptr(5, 10);
//     printf("%d\n", result);  // Expected output: 15
//     return 0;
// }


#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main() {
    int (*ops[2])(int, int) = {add, sub};

    printf("%d\n", ops[0](5, 2)); // 7
    printf("%d\n", ops[1](5, 2)); // 3
    return 0;
}


// #include <stdio.h>

// int square(int x) { return x * x; }

// int (*getFunc())(int) {
//     return square;
// }

// int main() {
//     int (*fp)(int) = getFunc();
//     printf("%d\n", fp(6)); // 36
//     return 0;
// }
