#include <stdio.h>

enum Color {
    RED,
    GREEN,
    BLUE
};

enum Status {
    PENDING = 10,
    APPROVED = 20,
    REJECTED = 30
};

int main() {
    enum Color c = RED;
    printf("Color RED = %d\n", c);
    
    c = GREEN;
    printf("Color GREEN = %d\n", c);
    
    c = BLUE;
    printf("Color BLUE = %d\n", c);
    
    enum Status s = APPROVED;
    printf("Status APPROVED = %d\n", s);
    
    s = REJECTED;
    printf("Status REJECTED = %d\n", s);
    
    return 0;
}
