#include<stdio.h>

int maxSubArraySum(int a[], int size)
{
    int max_so_far  = 0;
    int max_current = 0;

    int i;

    for(i = 1; i < size; i++)
    {
        max_current = max_current + a[i];
        if(max_current < 0)
            max_current = 0;
        if(max_current > max_so_far)
            max_so_far = max_current;
    }

    return max_so_far;
}

/* Driver program to test maxSubArraySum */
int main()
{
    int a[] =  {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(a)/sizeof(a[0]);
    int max_sum = maxSubArraySum(a, n);
    
    printf("Maximum contiguous sum is %u\n", max_sum);
    return 0;
}
