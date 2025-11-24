#include "string.h"

int strncmp(const char *a, const char *b, size_t n)
{
    while (n && *a && (*a == *b)) {
        n--;
        a++;
        b++;
    }

    return n ? *(const unsigned char *)a - *(const unsigned char *)b : 0;
}
