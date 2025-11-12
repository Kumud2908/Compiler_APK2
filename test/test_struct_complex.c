// Complex struct operations
#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Rectangle {
    struct Point topLeft;
    struct Point bottomRight;
};

int area(struct Rectangle r) {
    int width = r.bottomRight.x - r.topLeft.x;
    int height = r.bottomRight.y - r.topLeft.y;
    return width * height;
}

int main() {
    struct Point p1;
    p1.x = 0;
    p1.y = 0;
    
    struct Point p2;
    p2.x = 10;
    p2.y = 5;
    
    struct Rectangle rect;
    rect.topLeft = p1;
    rect.bottomRight = p2;
    
    printf("Rectangle area: %d\n", area(rect));  // 50
    
    // Pointer to struct
    struct Point *ptr = &p1;
    ptr->x = 5;
    ptr->y = 3;
    
    printf("Point: (%d, %d)\n", ptr->x, ptr->y);  // (5, 3)
    
    return 0;
}
