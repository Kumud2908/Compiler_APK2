
#include <stdio.h>
int main() {
int i = 0;
// for(; i < 5;) {
//     printf("%d\n", i);
//     i++;
// }

int a = 0;
for(int i = 0; i < 5 + (++a); i += a) {
    printf("%d %d\n", i, a);
}
}
