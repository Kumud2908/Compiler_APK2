#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30};
    int *p = arr;
    
    printf("Before: *p = %d\n", *p);
    p++;
    printf("After: *p = %d\n", *p);
    
    return 0;
}
