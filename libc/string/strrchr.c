#include "string.h"

char *strrchr(const char *s, int c)
{
    const char *last;
    unsigned char ch;

    ch = (unsigned char)c;

    while (*s) {
        if ((unsigned char)*s == ch) {
            last = s;
        }
        s++;
    }

    return (char *)((c == '\0') ? s : last);
}
