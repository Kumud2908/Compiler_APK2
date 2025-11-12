#include <stdio.h>

int main() {
    int x = 10;
    int y = 20;
    int *ptr;
    
    // Basic pointer operations
    ptr = &x;
    printf("x = %d\n", x);
    printf("*ptr = %d\n", *ptr);
    
    *ptr = 15;
    printf("After *ptr = 15, x = %d\n", x);
    
    // Point to y
    ptr = &y;
    printf("*ptr now points to y = %d\n", *ptr);
    
    // Pointer arithmetic
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = arr;
    
    printf("Array elements:\n");
    printf("p[0] = %d\n", p[0]);
    printf("p[1] = %d\n", p[1]);
    printf("p[2] = %d\n", p[2]);
    
    return 0;
}
