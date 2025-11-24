#include "string.h"

int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char *A = a;
    const unsigned char *B = b;

    while (n) {
        if (*A != *B) {
            return *A - *B;
        }
        n--;
        A++;
        B++;
    }

    return 0;
}
