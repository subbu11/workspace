#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    char *ipStr1 = "2001:11:2222:1223:4467:55:66:77";
    char *ipStr2 = "2001:11:2222:1223:4087:55:66:77";

    uint8_t sixteen = 16;
    //printf("sixteen : 0x%02X", sixteen);

    int prefixLength_save = 1;

    uint8_t netmask[16] = {0};

    uint32_t cidr = atoi(argv[1]);
    uint32_t i = 0;
    uint8_t one = 1;

    while(cidr >= 8)
    {
        netmask[i] |= 0xFF;

        cidr -= 8;
        i++;
    }

    //printf("\n%u, %u\n", cidr, i);
    //printf("0x%02X\n", ((one << (8 - cidr)) - 1));
    //printf("0x%02X\n", (~((one << (8 - cidr)) - 1)));
    
    netmask[i] |= (~((one << (8 - cidr)) - 1));

    printf("\n");
    int j = 0;
    for(j = 0; j < 16; j = j+2)
    {
        printf("%02X%02X ", netmask[j], netmask[j+1]);
    }
    printf("\n");

}
