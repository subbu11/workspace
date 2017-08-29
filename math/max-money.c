#include <stdio.h>

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int maxMoney(int *a, int n)
{
    int tmp[n+1] = {0};

    for(i = 1; i < n; i++)
    {
        /*if ith is selected*/
        int sum1 = 0;
        if(i-2 >= 0)
            sum1 = tmp[i-2] + tmp[i];

        /*if ith is not selected*/
        int sum2 = tmp[i-1];

        tmp[i] = max(sum1, sum2);
    }

    return tmp[n-1];
}
