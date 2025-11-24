#include <stdio.h>

// =========================
// TESTCASE 1: Pointer Arithmetic
// =========================
void testcase1() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p1 = arr;

    printf("\nTESTCASE 1: Pointer Arithmetic\n");
    printf("*(p+2) = %d\n", *(p1 + 2));     // 30
    printf("*(arr+4) = %d\n", *(arr + 4)); // 50
}

// =========================
// TESTCASE 2: Pointer To Pointer
// =========================
void testcase2() {
    int a = 100;
    int *p1 = &a;
    int **pp = &p1;

    printf("\nTESTCASE 2: Pointer to Pointer\n");
    printf("a = %d\n", a);
    printf("*p = %d\n", *p1);
    printf("**pp = %d\n", **pp);
}

// =========================
// TESTCASE 3: Swap using pointers
// =========================
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void testcase3() {
    int a = 5;
    int b = 10;

    printf("\nTESTCASE 3: Swap using pointers\n");
    printf("Before: a=%d b=%d\n", a, b);
    swap(&a, &b);
    printf("After : a=%d b=%d\n", a, b);
}

// =========================
// TESTCASE 4: Pointer to 2D Array
// =========================
void testcase4() {
    int arr[2][3] = {{1,2,3},{4,5,6}};
    int *p1 = &arr[0][0];

    printf("\nTESTCASE 4: Pointer to 2D Array\n");
    printf("arr[0][0] = %d\n", *(p1 + 0));  // 1
    printf("arr[1][2] = %d\n", *(p1 + 5));  // 6
    printf("arr[0][1] = %d\n", *(p1 + 1)); // 2
}

// =========================
// TESTCASE 5: Pointer with Struct
// =========================
struct Student {
    char name[20];
    int age;
};

void testcase5() {
    struct Student s;
    s.age = 21;
    struct Student *p1 = &s;

    printf("\nTESTCASE 5: Pointer with Struct\n");
    printf("Age via pointer = %d\n", p1->age);
    
    p1->age = 25;
    printf("Age after modification = %d\n", s.age);
}

// =========================
// TESTCASE 6: Pointer Assignment
// =========================
void testcase6() {
    int x = 42;
    int *p1 = &x;
    int *p2 = p1;  // Pointer aliasing

    printf("\nTESTCASE 6: Pointer Assignment\n");
    printf("x = %d, *p1 = %d, *p2 = %d\n", x, *p1, *p2);
    
    *p2 = 100;
    printf("After *p2 = 100:\n");
    printf("x = %d, *p1 = %d, *p2 = %d\n", x, *p1, *p2);
}

// =========================
// TESTCASE 7: Pointer with Array
// =========================
void testcase7() {
    int numbers[4] = {11, 22, 33, 44};
    int *p1 = numbers;

    printf("\nTESTCASE 7: Pointer with Array\n");
    printf("numbers[0] = %d\n", *(p1 + 0));
    printf("numbers[1] = %d\n", *(p1 + 1));
    printf("numbers[2] = %d\n", *(p1 + 2));
    printf("numbers[3] = %d\n", *(p1 + 3));
}

// =========================
// TESTCASE 8: Multiple Pointers
// =========================
void testcase8() {
    int val1 = 7;
    int val2 = 14;
    int *ptr1 = &val1;
    int *ptr2 = &val2;

    printf("\nTESTCASE 8: Multiple Pointers\n");
    printf("*ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2);
    
    int sum = *ptr1 + *ptr2;
    printf("Sum = %d\n", sum);
}

// =========================
// TESTCASE 9: Modify through pointer
// =========================
void testcase9() {
    int value = 50;
    int *p1 = &value;

    printf("\nTESTCASE 9: Modify through pointer\n");
    printf("Initial value = %d\n", value);
    
    *p1 = *p1 + 20;
    printf("After *p += 20: value = %d\n", value);
}

// =========================
// TESTCASE 10: Pointer with char array
// =========================
void testcase10() {
    char message[10] = "Hello";
    char *p1 = message;

    printf("\nTESTCASE 10: Pointer with char array\n");
    printf("First char = %c\n", *p1);
    printf("Second char = %c\n", *(p1 + 1));
    printf("Full string = %s\n", p1);
}

// =========================
// MAIN
// =========================
int main() {
    printf("==== POINTER TESTCASES ====\n");
    
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

    printf("\n==== ALL TESTS COMPLETED ====\n");
    return 0;
}
