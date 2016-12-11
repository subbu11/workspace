#include <iostream>
using namespace std;

int main()
{
    int i = 10;
    int j = 20;

    int& ref1  = i;
    ref1 = j;

    //int& const ref2 = i;
    //ref2 = j;

    const int& ref3 = i;
    //ref3 = j; // gives error

    const char *p1 = "aa";
    p1 = "bb";
    //*p1 = 'q'; // gives error
    
    char * const p2 = "aa";
    //p2 = "bb";
    *p2 = 'q';
}
