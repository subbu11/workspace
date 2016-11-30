#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    uint32_t one = 0x321232;
    printf("\t%04X \n", one);
    uint32_t two = ntohs(one);
    printf("\t%04X \n", one);
    printf("\t%04X \n", two);
}
