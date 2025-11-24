#include <stdio.h>

// Global typedefs
typedef int INTEGER;
typedef int* IntPtr;

struct Point {
    int x;
    int y;
};

typedef struct Point PointType;

// =============================
// TESTCASE 1: typedef primitive
// =============================
void testcase1() {
    INTEGER x = 50;
    printf("\nTESTCASE 1: typedef primitive\n");
    printf("x = %d\n", x);
}

// =============================
// TESTCASE 2: typedef pointer
// =============================
void testcase2() {
    int a = 10;
    IntPtr p = &a;
    printf("\nTESTCASE 2: typedef pointer\n");
    printf("*p = %d\n", *p);
}

// =============================
// TESTCASE 3: typedef pointer-to-pointer
// =============================
void testcase3() {
    typedef int** IntPtrPtr;
    
    int x = 99;
    int* p = &x;
    IntPtrPtr pp = &p;

    printf("\nTESTCASE 3: typedef pointer-to-pointer\n");
    printf("**pp = %d\n", **pp);
}

// =============================
// TESTCASE 4: typedef struct (named)
// =============================
void testcase4() {
    PointType pt;
    pt.x = 10;
    pt.y = 20;

    printf("\nTESTCASE 4: typedef struct\n");
    printf("Point: (%d, %d)\n", pt.x, pt.y);
}

// =============================
// TESTCASE 5: typedef with enum
// =============================
void testcase5() {
    typedef enum { RED, GREEN, BLUE } Color;
    
    Color c = GREEN;

    printf("\nTESTCASE 5: typedef with enum\n");
    printf("Enum value = %d\n", c);
}

// =============================
// TESTCASE 6: Multiple typedef in same function
// =============================
void testcase6() {
    typedef int Type1;
    typedef int Type2;
    
    Type1 a = 100;
    Type2 b = 200;

    printf("\nTESTCASE 6: multiple typedef\n");
    printf("a = %d, b = %d\n", a, b);
}

// =============================
// TESTCASE 7: typedef in nested scope
// =============================
void testcase7() {
    typedef int OuterInt;
    OuterInt x = 42;
    
    printf("\nTESTCASE 7: typedef in nested scope\n");
    printf("x = %d\n", x);
    
    if (x > 0) {
        typedef int InnerInt;
        InnerInt y = 84;
        printf("y = %d\n", y);
    }
}

// =============================
// TESTCASE 8: typedef for unsigned types
// =============================
void testcase8() {
    typedef int UInt;
    
    UInt num = 65535;

    printf("\nTESTCASE 8: typedef for unsigned\n");
    printf("num = %d\n", num);
}

// =============================
// MAIN
// =============================
int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    testcase8();

    printf("\nAll typedef tests completed!\n");
    return 0;
}
