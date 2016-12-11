#include <iostream>
#include <map>
#include <iterator>

using namespace std;

int main()
{
    multimap<int, int> s;
    multimap<int, int>::iterator it;

    s.insert(pair<int, int>(30, 300));
    s.insert(pair<int, int>(40, 400));
    s.insert(pair<int, int>(10, 100));
    s.insert(pair<int, int>(100, 1000));
    s.insert(pair<int, int>(100, 1001));
     
    cout << "MAP" << endl;
    for(it = s.begin(); it != s.end(); it++)
    {
        cout << it->first << "\t" << it->second << endl;
    }
    /*
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
*/
}
