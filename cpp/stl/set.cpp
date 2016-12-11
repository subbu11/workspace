#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> s;
    set<int>::iterator it;

    s.insert(30);
    s.insert(40);
    s.insert(10);
    s.insert(100);

    for(it = s.begin(); it != s.end(); it++)
    {
        cout << *it << endl;
    }

    set<int, greater<int> > s2;
    set<int, greater<int> >::iterator it2;

    s2.insert(30);
    s2.insert(40);
    s2.insert(10);
    s2.insert(100);

    for(it2 = s2.begin(); it2 != s2.end(); it2++)
    {
        cout << *it2 << endl;
    }

}
