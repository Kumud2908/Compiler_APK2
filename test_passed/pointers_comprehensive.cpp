// Complex pointer operations
#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    int *p1 = &a;
    int *p2 = &b;
    int **pp = &p1;
    
    // Pointer arithmetic and dereferencing
    printf("a = %d\n", *p1);        // 10
    printf("b = %d\n", *p2);        // 20
    printf("*pp = %d\n", **pp);     // 10
    
    // Swap using pointers
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    
    printf("After swap:\n");
    printf("a = %d\n", a);          // 20
    printf("b = %d\n", b);          // 10
    
    // Array and pointer
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    
    printf("Array elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
    
    return 0;
}
