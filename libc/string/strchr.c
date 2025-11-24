#include "string.h"

char *strchr(const char *s, int c)
{
    unsigned char ch;
    
    ch = (unsigned char)c;

    while (*s) {
        if ( (unsigned char)*s == ch ) {
            return (char *)s;
        }
        s++;
    }

    return (ch == '\0') ? (char *)s : NULL;
}
