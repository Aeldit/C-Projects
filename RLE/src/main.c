#include <stdio.h>

#include "rle.h"

int main(void)
{
    // char *s = compress("aaaaaaaab", 8);
    //  char *s = compress("aaaaaaaaaaaaaaabbbbbbbccd", 8);
    // char *s = compress("aaaaaaaaaaaabGGGGGGGGGGaaaaaa", 10);
    // char *s = compress("9999999999888887777799999", 16);
    //  char *s = decompress("7A6hf%", 16);
    // char *s = compress("", 8);
    char *s = decompress("", 8);
    if (s == NULL)
    {
        printf("NULL");
        return 0;
    }
    printf("'%s'", s);
    free(s);
    return 0;
}
