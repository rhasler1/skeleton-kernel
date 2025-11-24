#include "fdt_stubs.h"

size_t strlen(const char *s)
{
    size_t n = 0;
    while (*s++)
        n++;
    return n;
}

void *memcpy(void *d, const void *s, size_t n)
{
    unsigned char*D=d;
    const unsigned char*S=s;
    while(n--) *D++=*S++; return d;
}

void *memmove(void *d, const void *s, size_t n)
{
    unsigned char*D=d;
    const unsigned char*S=s;
    if(D<S){
        while(n--)*D++=*S++;
    }
    else{
        D+=n;
        S+=n;
        while(n--)*--D=*--S;
    }
    return d;
}

int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char*A=a,*B=b;
    for(;n--;A++,B++) if(*A!=*B) return *A-*B;
    return 0;
}

void *memset(void *d, int c, size_t n)
{
    unsigned char*D=d;
    while(n--)*D++=(unsigned char)c;
    return d;
}

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    for (; n--; p++)
        if (*p == (unsigned char)c)
            return (void *)p;
    return NULL;
}

size_t strnlen(const char *s, size_t maxlen) {
    size_t n = 0;
    while (n < maxlen && s[n]) n++;
    return n;
}

char *strchr(const char *s, int c) {
    unsigned char ch = (unsigned char)c;
    for (; *s; s++) if ((unsigned char)*s == ch) return (char *)s;
    return (ch == 0) ? (char *)s : NULL;
}

char *strrchr(const char *s, int c) {
    const char *last = NULL;
    unsigned char ch = (unsigned char)c;
    for (; *s; s++) if ((unsigned char)*s == ch) last = s;
    return (char *)((c == 0) ? s : last);
}

int strncmp(const char *a, const char *b, size_t n) {
    for (; n && *a && (*a == *b); n--, a++, b++);
    return n ? *(const unsigned char *)a - *(const unsigned char *)b : 0;
}

int strcmp(const char *a,const char *b)
{
    while(*a && *a==*b){a++;b++;}
    return *(const unsigned char*)a-*(const unsigned char*)b;
}
