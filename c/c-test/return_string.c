/*
 * Function can return array which is on its stack 
 * 
 */

#include <stdio.h>
#include <string.h>

char* getStr()
{
    char s[6];

    s[0] = 'H';
    s[1] = 'E';
    s[2] = 'L';
    s[3] = 'L';
    s[4] = 'O';
    s[5] = '\0';

    //printf("%s\n", s);

    return s;
}

int main()
{
    printf("string returned : %s\n", getStr());
}
