#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =========================
// TESTCASE 1: Pointer Arithmetic
// =========================
void testcase1() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    printf("\nTESTCASE 1: Pointer Arithmetic\n");
    printf("*(p+2) = %d\n", *(p + 2));     // 30
    printf("*(arr+4) = %d\n", *(arr + 4)); // 50
    p++;
    printf("*p after p++ = %d\n", *p);     // 20
}

// =========================
// TESTCASE 2: Pointer To Pointer
// =========================
void testcase2() {
    int a = 100;
    int *p = &a;
    int **pp = &p;

    printf("\nTESTCASE 2: Pointer to Pointer\n");
    printf("a = %d\n", a);
    printf("*p = %d\n", *p);
    printf("**pp = %d\n", **pp);
}

// =========================
// TESTCASE 3: Array of Pointers
// =========================
void testcase3() {
    char *names[] = {"Alice", "Bob", "Charlie"};
    
    printf("\nTESTCASE 3: Array of Pointers\n");
    for (int i = 0; i < 3; i++) {
        printf("names[%d] = %s\n", i, names[i]);
    }
}

// =========================
// TESTCASE 4: Pointer to Function
// =========================
int add(int a, int b) { return a + b; }

void testcase4() {
    int (*fp)(int, int) = add;

    printf("\nTESTCASE 4: Pointer to Function\n");
    printf("add(5,7) using fp = %d\n", fp(5, 7));
}

// =========================
// TESTCASE 5: Void Pointer
// =========================
void testcase5() {
    int a = 10;
    float b = 5.5;
    void *vp;

    printf("\nTESTCASE 5: Void Pointer\n");

    vp = &a;
    printf("Value at void* int = %d\n", *(int*)vp);

    vp = &b;
    printf("Value at void* float = %.1f\n", *(float*)vp);
}

// =========================
// TESTCASE 6: Pointer with Struct
// =========================
struct Student {
    char name[20];
    int age;
};

void testcase6() {
    struct Student s = {"Riya", 21};
    struct Student *p = &s;

    printf("\nTESTCASE 6: Pointer with Struct\n");
    printf("Name = %s, Age = %d\n", p->name, p->age);
}

// =========================
// TESTCASE 7: Dangling Pointer Example
// =========================
int* getDanglingPtr() {
    int x = 50;  // local variable
    return &x;   // returning address → dangling
}

void testcase7() {
    printf("\nTESTCASE 7: Dangling Pointer (unsafe)\n");
    int *dp = getDanglingPtr();
    printf("Dangling pointer value (undefined) = %d\n", *dp);
}

// =========================
// TESTCASE 8: Double Free Error
// =========================
void testcase8() {
    printf("\nTESTCASE 8: Double Free (dangerous)\n");

    int *ptr = malloc(4);
    *ptr = 999;
    printf("Value = %d\n", *ptr);

    free(ptr);
    printf("Freed once\n");

    // free(ptr);   // Uncomment to test double free crash
    printf("Double free avoided (commented out)\n");
}

// =========================
// TESTCASE 9: Swap using pointers
// =========================
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void testcase9() {
    int a = 5, b = 10;

    printf("\nTESTCASE 9: Swap using pointers\n");
    printf("Before: a=%d b=%d\n", a, b);
    swap(&a, &b);
    printf("After : a=%d b=%d\n", a, b);
}

// =========================
// TESTCASE 10: Pointer to 2D Array
// =========================
void testcase10() {
    int arr[2][3] = {{1,2,3},{4,5,6}};
    int (*p)[3] = arr;  // pointer to array of 3 ints

    printf("\nTESTCASE 10: Pointer to 2D Array\n");
    printf("p[1][2] = %d\n", p[1][2]);  // 6
    printf("*(*(p+0)+1) = %d\n", *(*(p+0)+1)); // 2
}


// =========================
// MAIN
// =========================
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

    return 0;
}
