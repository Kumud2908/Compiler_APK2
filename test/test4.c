// Test Case 4: Enum, Union

#include <stdio.h>

enum Days { MON, TUE, WED, THU, FRI, SAT, SUN };

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    enum Days today = WED;
    printf("Today is day number: %d\n", today);

    union Data data;
    data.i = 10;
    printf("Integer: %d\n", data.i);

    data.f = 220.5;
    printf("Float: %.2f\n", data.f);

    return 0;
}