int peak(int arr[], int n)
{
    int i = 0;

    for(i = 0; i < n; i++)
    {
        int prev = 0;
        int next = 0;

        if(i-1 >= 0)
            prev = arr[i-1];
        if(i+1 <= n-1)
            next = arr[i+1];

        if(arr[i] >= prev && arr[i] <= next)
            printf("%u ", arr[i]);
    }
}
