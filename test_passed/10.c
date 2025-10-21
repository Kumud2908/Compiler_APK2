/* 
 * Feature: Multi-level Pointers
 * File   : multi_level_pointer.c
 * Desc   : Demonstrates pointer to pointer
 */
#include <stdio.h>

int main() {
    int a,*b;
    int *p = &a;
    int **pp = &p;
    
    printf("Value = %d\n", **pp);
    return 0;
}
