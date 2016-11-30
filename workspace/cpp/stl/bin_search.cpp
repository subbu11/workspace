#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a[6] = {56, 34, 2, 66, -1, 1};
    
    sort(a, a+6);
    for(int i = 0; i < 6; i++)
        cout << '\t' <<a[i];

    cout << "\n";
    
  
    /*
     * binary_search(fisrt, last, value)
     * searchinh is done for [first, last) 
     * i.e. last element is not included
     */
    if(binary_search(a, a+6, 2))
    {
        cout << "element " << 2 << " found" << "\n";
    }
    else
    {
        cout << "element " << 2 << " not found\n ";
    }
    
    if(binary_search(a, a+6, 20))
    {
        cout << "element 2 found" << "\n";
    }
    else
    {
        cout << "element 20 not found\n ";
    }
  
    cout << "\n";
}

