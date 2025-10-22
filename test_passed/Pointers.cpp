#include <stdio.h>


class Point {
    int x, y;
    void set(int a, int b) {
        x = a;
        y = b;
    }
    int sum() {
        return x + y;
    }
};
int main(){
    Point p;
p.set(2, 3);
int s = p.sum();

}

