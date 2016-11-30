#include <iostream>
#include <queue>

using namespace std;

void show_priority_queue(priority_queue<int> pq)
{
    while(!pq.empty())
    {
        cout << pq.top() << "\t";
        pq.pop();
    }

    cout << "\n";
}

int main()
{
    priority_queue<int> pq;
    
    cout << "Priority Queue :: " << endl;
    pq.push(10);
    pq.push(20);
    pq.push(30);
    pq.push(40);

    show_priority_queue(pq);
    
    cout << "pq.pop() :: " << endl;
    
    pq.pop();
    show_priority_queue(pq);
}
