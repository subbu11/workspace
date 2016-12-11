#include <stdio.h>
#include <limits.h>

int cutRod(int price[], int num)
{
    int i = 0, j = 0;

    /*why tmp array size is (num + 1) ?*/
    int tmp[num + 1];

    tmp[0] = 0;
    for(i = 1; i <= num; i++)
    {
        int max_val = INT_MIN;

        /*why j is started from 0 and not 1 ?*/
        for(j = 0; j <= i; j++)
        {
            /* find j such that tmp[i] is maximum */
            if(max_val < (price[j] + tmp[i - j - 1]))
            {
                max_val = price[j] + tmp[i - j - 1];
            }
        }
        tmp[i] = max_val;
    }

    return tmp[num];
}

int main()
{
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    getchar();
    return 0;
}
