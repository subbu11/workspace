#include <iostream>
#include <deque>
#include <iterator>

using namespace std;

void show_deque(deque<int> q)
{
    deque<int> :: iterator itr;

    for(itr = q.begin(); itr != q.end(); ++itr)
    {
        cout << *itr << "\t";
    }

    cout << "\n";
}

int main()
{
    deque<int> q;

    for(int i = 1; i < 10; i++)
    {
        q.push_back(i*2);
    }

    show_deque(q);
    
    cout << q.at(4) << endl;

    q.pop_front();

    show_deque(q);

    q.push_back(100);

    show_deque(q);
}
