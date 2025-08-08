// Test Case 3: Variable argument function (ellipsis '...') and va_list usage.
#include <stdarg.h>

void myprintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    /* pretend to handle args */
    va_end(ap);
}

int main() {
    myprintf("Hello %d", 5);
    return 0;
}