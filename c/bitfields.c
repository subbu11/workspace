#include <stdio.h>

struct
{
    /*note : default data type is int*/
    unsigned a : 3;
    unsigned b : 31;
} s;

int main()
{
    printf("size of s: %u bytes\n", sizeof(s));
}
