#include "string.h"

void *memset(void *d, int c, size_t n)
{
    unsigned char *D;

    D = d;

    while (n) {
        *D++ = (unsigned char)c;
        n--;
    }

    return d;
}
