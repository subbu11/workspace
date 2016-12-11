#include <stack>
#include <iostream>

using namespace std;


void show_stack(stack<int> s)
{
    while(!s.empty())
    {
        cout << s.top() << "\t";
        s.pop();
    }

    cout << "\n";
}

int main()
{
    stack<int> s;
    
    cout << "Stack :: " << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    show_stack(s);
    
    cout << "S.pop() :: " << endl;
    
    s.pop();
    show_stack(s);
}
