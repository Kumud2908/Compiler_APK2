/* 
 * Feature: until loop (do-while equivalent in C)
 * File   : until_loop.c
 * Desc   : Demonstrates do-while loop execution
 */


 //do while loop is not implemented in the grammar so is not tested
#include <stdio.h>

int main() {
    int x = 0;
    do {
        printf("%d ", x);
        x++;
    } while(x < 5);
    return 0;
}
