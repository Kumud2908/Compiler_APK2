/* 
 * Feature: typedef
 * File   : typedef.c
 * Desc   : Demonstrates typedef with unsigned int
 */
#include <stdio.h>

typedef unsigned  uint;

int main() {
    uint a = 10;
    printf("%u", a);
    return 0;
}
