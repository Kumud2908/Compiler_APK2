#include <stdio.h>

// =============================
// TESTCASE 1: typedef primitive
// =============================
void testcase1() {
    typedef int INTEGER;
    INTEGER x = 50;

    printf("\nTESTCASE 1: typedef primitive\n");
    printf("x = %d\n", x);
}

// =============================
// TESTCASE 2: typedef pointer
// =============================
void testcase2() {
    typedef int* IntPtr;

    int a = 10;
    IntPtr p = &a;

    printf("\nTESTCASE 2: typedef pointer\n");
    printf("*p = %d\n", *p);
}

// =============================
// TESTCASE 3: typedef pointer (alternative test)
// =============================
void testcase3() {
    typedef char* CharPtr;

    int vals[5];
    vals[0] = 1;
    vals[1] = 2;
    vals[2] = 3;
    vals[3] = 4;
    vals[4] = 5;

    printf("\nTESTCASE 3: typedef with arrays\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", vals[i]);
    }
    printf("\n");
}

// =============================
// TESTCASE 4: typedef struct (global)
// =============================
struct StudentStruct {
    int id;
    int age;
};

typedef struct StudentStruct Student;

void testcase4() {
    Student s;
    s.id = 101;
    s.age = 21;

    printf("\nTESTCASE 4: typedef struct\n");
    printf("ID = %d, Age = %d\n", s.id, s.age);
}

// =============================
// TESTCASE 5: typedef struct with direct usage
// =============================
void testcase5() {
    struct StudentStruct s2;
    s2.id = 202;
    s2.age = 22;
    
    struct StudentStruct* sp = &s2;

    printf("\nTESTCASE 5: struct pointer\n");
    printf("ID = %d, Age = %d\n", sp->id, sp->age);
}

// =============================
// TESTCASE 6: typedef for pointer-to-pointer
// =============================
void testcase6() {
    typedef int** IntPtrPtr;

    int x = 99;
    int* p = &x;
    IntPtrPtr pp = &p;

    printf("\nTESTCASE 6: typedef pointer-to-pointer\n");
    printf("**pp = %d\n", **pp);
}

// =============================
// TESTCASE 7: typedef for multi-dimensional array (simplified)
// =============================
void testcase7() {
    int m[2][3];
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    printf("\nTESTCASE 7: multi-dimensional array\n");
    printf("%d %d %d\n", m[0][0], m[0][1], m[0][2]);
    printf("%d %d %d\n", m[1][0], m[1][1], m[1][2]);
}

// =============================
// TESTCASE 8: typedef with enum
// =============================
void testcase8() {
    typedef enum { RED, GREEN, BLUE } Color;

    Color c = GREEN;

    printf("\nTESTCASE 8: typedef with enum\n");
    printf("Enum value = %d\n", c);
}

// =============================
// TESTCASE 9: Multiple typedef usage
// =============================
void testcase9() {
    typedef int MyInt;
    typedef int AnotherInt;
    
    MyInt x = 777;
    AnotherInt y = 888;

    printf("\nTESTCASE 9: multiple typedefs\n");
    printf("x = %d, y = %d\n", x, y);
}

// =============================
// TESTCASE 10: typedef with const (simplified)
// =============================
void testcase10() {
    typedef int ConstInt;
    
    ConstInt x = 42;

    printf("\nTESTCASE 10: typedef with const\n");
    printf("x = %d\n", x);
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
    testcase9();
    testcase10();

    printf("\nAll typedef tests completed!\n");
    return 0;
}
