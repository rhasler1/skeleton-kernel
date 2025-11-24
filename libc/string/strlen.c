#include "string.h"

size_t strlen(const char *s)
{
    size_t n;

    n = 0;
    
    while (*s++) {
        n++;
    }

    return n;
}
