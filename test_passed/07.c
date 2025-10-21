/* 
 * Feature: enum, union
 * File   : enum_union.c
 * Desc   : Demonstrates enumeration and union usage
 */
#include <stdio.h>

enum Days { MON, TUE, WED };
union Data { int i; float f; };

int main() {
    enum Days d = WED;
    printf("Day: %d\n", d);

    union Data data;
    data.i = 10;
    printf("Data.i = %d\n", data.i);
    return 0;
}
