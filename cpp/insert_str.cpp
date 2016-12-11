#include <iostream>
#include <stdint.h>
#include <string.h>

using namespace std;

int main()
{
    uint8_t buf[16] = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                       0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65};
   
    char cbuf[16];
    memcpy(cbuf, buf, 16);

    string str;
    str.insert(0, cbuf, 16);

    cout << "string : " << str.c_str();
}
