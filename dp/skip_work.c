#include <stdio.h>

int min(int a, int b)
{
    return (a < b ? a : b);
}

int minTime(int work[], int n)
{
    int tmp[n][2];

    int i = 0;

    tmp[0][0] = 0;
    tmp[0][1] = work[0];

    tmp[1][0] = tmp[0][1];
    tmp[1][1] = min(work[0], work[1]);

    for(i = 2; i < n; i++)
    {
        tmp[i][0] = tmp[i-1][1];

        tmp[i][1] = min( 
                work[i] + tmp[i-1][1],
                work[i] + tmp[i-2][1]);
    }

    return min(tmp[n-1][0], tmp[n-1][1]);
}

int main()
{
    int work1[] = {22, 10, 15, 3, 5};
    printf("Minimum Time : %u\n", minTime(work1, sizeof(work1)/ sizeof(work1[0]) ) );

    int work2[] = {5, 6, 7, 8, 9, 10};
    printf("Minimum Time : %u\n", minTime(work2, sizeof(work2)/ sizeof(work2[0]) ) ); 

}
