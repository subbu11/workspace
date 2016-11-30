#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main()
{
    pair <string, int> p1;
    pair <string, int> p2(string("two"), 2); 
    pair <string, int> p3(string("three"), 3); 

    p1.first = string("one");
    p1.second = 1;

    cout << "p1 : " << p1.first << " " << p1.second << endl;
    cout << "p2 : " << p2.first << " " << p2.second << endl;
    
    cout << "after swapping p1 and p2" << endl;
    swap(p1, p2);

    cout << "p1 : "<< p1.first << " " << p1.second << endl;
    cout << "p2 : "<<p2.first << " " << p2.second << endl;

    cout << "after p1 = p3" << endl;
    p1 = p3;

    cout << "p1 : " << p1.first << " " << p1.second << endl;
    cout << "p2 : " <<p2.first << " " << p2.second << endl;

    cout << "after p4(p2)" << endl;
    pair <string, int> p4(p2);
    cout << "p4 : " << p4.first << " " << p4.second << endl;

}
