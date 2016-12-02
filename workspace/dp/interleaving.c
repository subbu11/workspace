#include <stdio.h>

int isInterleaved(char *A, char *B, char *C)
{
    // Iterate through all characters of C.
    while (*C != 0)
    {
        // Match first character of C with first character
        // of A. If matches them move A to next 
        if (*A == *C)
            A++;

        // Else Match first character of C with first 
        // character of B. If matches them move B to next 
        else if (*B == *C)
            B++;

        // If doesn't match with either A or B, then return
        // false
        else
            return 0;

        // Move C to next for next iteration
        C++;
    }

    // If A or B still have some characters, then length of
    // C  is smaller than sum of lengths of A and B, so 
    // return false
    if (*A || *B)
        return 0;

    return 1;
}

int isInterleaved2(char *a, char *b, char *c)
{
    if ( !(*a) && !(*b) && !(*c))
        return 1;
    
    if(*c == '\0')
        return 0;

    return (
            (*c == *a) && (isInterleaved2(a+1, b, c+1))
            || 
            (*c == *b) && (isInterleaved2(a, b+1, c+1))
           );
}

int main()
{
    char *A = "AB";
    char *B = "CD";
    char *C = "ACBG";

    if (isInterleaved2(A, B, C) == 1)
        printf("%s is interleaved of %s and %s\n", C, A, B);
    else
        printf("%s is not interleaved of %s and %s\n", C, A, B);

    return 0;
}
