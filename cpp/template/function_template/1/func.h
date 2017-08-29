#include <iostream>
#include <typeinfo>

using namespace std;

/* Template declaration */
template <typename T>
void printType(T t)
{
    cout << "Type --> " <<  typeid(t).name()  << endl;
}

