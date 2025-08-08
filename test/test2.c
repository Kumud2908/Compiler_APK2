// Test Case 2: Arrays (int/char), pointers, structure, printf/scanf, function call with arguments

#include <stdio.h>

struct Student {
    char name[20];
    int age;
};

void displayStudent(struct Student s) {
    printf("Name: %s, Age: %d\n", s.name, s.age);
}

int main() {
    int arr[3] = {1, 2, 3};
    char str[6] = "Hello";

    int *p = arr; // pointer
    printf("First element via pointer: %d\n", *p);

    struct Student stu = {"Alice", 20};
    displayStudent(stu);

    printf("Enter student age: ");
    scanf("%d", &stu.age);
    printf("Updated Age: %d\n", stu.age);

    return 0;
}