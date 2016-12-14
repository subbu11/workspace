/*
 * Map iteration technqiues
 */
#include <iostream>
#include <map>
#include <iterator>

using namespace std;

int main()
{
    map<int, int> s;
    map<int, int>::iterator it;

    s.insert(pair<int, int>(30, 300));
    s.insert(pair<int, int>(40, 400));
    s.insert(pair<int, int>(10, 100));
    s.insert(pair<int, int>(100, 1000));
    s.insert(pair<int, int>(100, 1001));

    cout << "MAP" << endl;
    it = s.begin();
    while(it != s.end())
    {
        cout << it->first << "\t" << it->second << endl;
    }
    
    cout << "MAP 2" << endl;
    for(pair<int,int> p : s)
    {
        int a = p.first;
        int b = p.second;

        cout << a << "\t" << b << endl;
    }

    cout << "MAP 3" << endl;
    for_each(s.begin(), s.end(), [](pair<int, int> p)
            {
                int a = p.first;
                int b = p.second;

                cout << a << "\t" << b << endl;
            });
}
