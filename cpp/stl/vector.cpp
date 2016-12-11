#include <iostream>
#include <string>
#include <vector>



using namespace std;

int main()
{
    vector <int> v;
    vector <int> :: iterator itr;
    
    cout << "vector empty : "<< v.empty() << endl;
    cout << "vector size : "<< v.size() << endl;
    cout << "vector capacity : "<< v.capacity() << endl;
    cout << "vector max-size : "<< v.max_size() << endl;

    for(int i = 1; i <= 5; i++)
    {
        v.push_back(i);
    }

    for(itr = v.begin(); itr != v.end(); itr++)
    {
        cout << *itr << endl;
    }

    cout << "vector empty : "<< v.empty() << endl;
    cout << "vector size : "<< v.size() << endl;
    cout << "vector capacity : "<< v.capacity() << endl;
    cout << "vector max-size : "<< v.max_size() << endl;
    
    /* resize to 10 elements */
    cout << "After resizing to 10 elements" << endl;
    v.resize(10, 1000);
    for(itr = v.begin(); itr != v.end(); itr++)
    {
        cout << *itr << endl;
    }

    /* resize to 3 elements */
    cout << "After resizing to 3 elements" << endl;
    v.resize(3, 1000); // or v.resize(3);
    for(itr = v.begin(); itr != v.end(); itr++)
    {
        cout << *itr << endl;
    }
}
