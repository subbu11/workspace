#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a[6] = {56, 34, 2, 66, -1, 1};
    
    for(int i = 0; i < 6; i++)
        cout << '\t' <<a[i];

    cout << "\n";
    
    /*
     * sort(fisrt, last)
     * sorting is done for [first, last) 
     * i.e. last element is not included
     */
    sort(a, a+5);

    for(int i = 0; i < 6; i++)
        cout << '\t' <<a[i];

    cout << "\n";
}

