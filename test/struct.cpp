#include <stdio.h>

struct Address {
    int houseNo;
    int zip;
};

struct Person {
    char name[20];
    struct Address addr;
};

int main() {
    struct Person p;
    p.addr.houseNo = 45;
    p.addr.zip = 12345;
    printf("%d %d\n", p.addr.houseNo, p.addr.zip);
    return 0;
}
