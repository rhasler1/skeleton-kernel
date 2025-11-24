#include "string.h"

void *memmove(void *d, const void *s, size_t n)
{
    unsigned char *D;

    D = d;

    const unsigned char *S = s;

    if (D < S) {
        while (n) {
            *D++ = *S++;
            n--;
        }
    }
    else {
        D += n;
        S += n;
        while (n) {
            *--D = *--S;
            n--;
        }
    }

    return d;
}
