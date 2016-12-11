/* Dynamic Programming C/C++ implementation of LCS problem */
#include <stdio.h>
#include <string.h>

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
char* lcs( char *X, char *Y, int m, int n )
{
    int L[m+1][n+1];
    int i, j;

    /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
     *       that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;

            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }

    /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
    int length = L[m][n];

    /* char array to store LCS string */
    char lcsStr[length + 1];

    lcsStr[length] = '\0';
    int index = length - 1;

    i = m;
    j = n;

    while(i > 0 && j >0)
    {
        if(X[i] == Y[j])
        {
            i--;
            j--;

            lcsStr[index] = X[i];
            index--;
        }
        else if(L[i-1][j] > L[i][j-1])
        {
            i--;
        }
        else 
        {
            j--;
        }
    }

    printf("LCS ::: %s\n", lcsStr);
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Driver program to test above function */
int main()
{
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);

    lcs( X, Y, m, n );

    return 0;
}
