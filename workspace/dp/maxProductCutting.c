#include <stdio.h>
#include <limits.h>

int maxProd(int n)
{
    int i = 0; 
    int k = 0;

    /*will return value of tmp[n]*/
    int tmp[n+1];

    tmp[0] = 0;
    for(i = 1; i <= n; i++)
    {
        int max_prod = INT_MIN;
        for(k = 1; k <= i; k++)
        {
            if(max_prod < ( k* tmp[i-k]) )
            {
                max_prod = k * tmp[i-k];
            }
        }
        tmp[i] = max_prod;
    }
}

int main()
{
    cout << "Maximum Product is " << maxProd(10);
    return 0;
}
