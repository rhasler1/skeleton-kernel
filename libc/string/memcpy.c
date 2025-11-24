#include "string.h"

void *memcpy(void *d, const void *s, size_t n)
{
    unsigned char *D;

    D = d;

    const unsigned char *S = s;

    while (n) {
        *D++ = *S++;
        n--;
    }
    
    return d;
}
