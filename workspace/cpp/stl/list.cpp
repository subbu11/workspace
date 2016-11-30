#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void show_list(list<int> l)
{
    list<int> :: iterator itr;

    for(itr = l.begin(); itr != l.end(); itr++)
    {
        cout << *itr << "\t";
    }

    cout << "\n" ;
}

int main()
{
    list<int> l;

    for(int i = 0; i < 10; i++)
    {
        l.push_front(i*3);
    }

    show_list(l);

    l.push_back(10);
    
    show_list(l);

    l.reverse();

    show_list(l);

    l.sort();
    
    show_list(l);

    l.pop_front();

    show_list(l);

    l.pop_back();

    show_list(l);
}
