#include <iostream>
#include <queue>

using namespace std;

void show_queue(queue<int> q)
{
    while(!q.empty())
    {
        cout << q.front() << "\t";
        q.pop();
    }

    cout << "\n";
}

int main()
{
    queue<int> q;
    
    cout << "Queue :: " << endl;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    show_queue(q);
    
    cout << "q.pop() :: " << endl;
    
    q.pop();
    show_queue(q);
}
