#include <stdio.h>

struct pair
{
    int a;
    int b;
};

int maxChainLength(struct pair pairs[], int num)
{
    int i = 0, j = 0, max = 0;
    int *mcl = (int *)malloc(sizeof(int) * num);

    /*initialise*/
    for(i = 0; i < num; i++)
    {
        mcl[i] = 1;
    }

    /*mcl for each of the elements*/
    for(i = 1; i < num; i++)
    {
        for(j = 0; j < i; j++)
        {
            /* condition for chaining */
            if((pairs[i].a  > pairs[j].b) 
                && (mcl[i] < mcl[j] + 1))
            {
                mcl[i] = mcl[j] + 1;
            }
        }
    }

    /*find max*/
    for(i = 0; i < num; i++)
    {
        if(max < mcl[i])
        {
            max = mcl[i];
        }
    }

    return max;
}

/* Driver program to test above function */
int main()
{
    struct pair arr[] = { {5, 24}, {15, 25},
        {27, 40}, {50, 60} };
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Length of maximum size chain is %d\n",
            maxChainLength( arr, n ));
    return 0;
}
