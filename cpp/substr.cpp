#include <iostream>
#include <string.h>

using namespace std;

void handle(std::string s)
{
    cout << s.c_str() << endl;

    int len = s.length();

    std::string t = s.substr(len + 10, len + 100000000000000000);
}

int main() {

    try
    {
        handle(std::string("whoa"));
    }
    catch(...)
    {
        cout << "haha" << endl;
    }

    return 0;
}
