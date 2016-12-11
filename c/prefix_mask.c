#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main()
{
    char *ipStr1 = "2001:11:2222:1223:4467:55:66:77"; 
    char *ipStr2 = "2001:11:2222:1223:4087:55:66:77";
    int prefixLength_save = 65;
    int prefixLength = prefixLength_save;

    uint64_t ip[2] = {0};
    uint64_t filter[2] = {0};
    inet_pton(AF_INET6, ipStr1, ip);
    inet_pton(AF_INET6, ipStr2, filter);

    printf("IP :    \t");
    int i = 0;
    for(i = 0; i < 2; i++)
    {
        printf("%08X ", ip[i]);
    }
    printf("\n");

    i = 0;
    printf("Filter :\t");
    for(i = 0; i < 2; i++)
    {
        printf("%08X ", filter[i]);
    }
    printf("\n");

    uint64_t one = 1;

    /*mask ip with prefix-length*/
    uint64_t newIp[2] = {0};
    
    i = 0;
    while(prefixLength > 64)
    {
        newIp[i] = ip[i];
        
        printf("\tnewIp : %08X, ip : %08X, prefixLength = %u\n", newIp[i], ip[i], prefixLength);

        prefixLength -= 64;
        i++;
    }
    
    //printf("newIp : %08X mask : %08X\n", ip[i], ((one << prefixLength) - 1));
    
    newIp[i] = ip[i] & (((one << prefixLength) - 1));
    printf("\tnewIp : %08X, ip : %08X, prefixLength = %u\n", newIp[i], ip[i], prefixLength);

    printf("newIp :    \t");
    i = 0;
    for(i = 0; i < 2; i++)
    {
        printf("%08X ", newIp[i]);
    }
    printf("\n");

    /*mask filter-ip with prefix-length*/
    uint64_t newFilter[2] = {0};
    prefixLength = prefixLength_save;
 
    i = 0;
    while(prefixLength > 64)
    {
        newFilter[i] = filter[i];
        
        printf("\tnewFilter : %08X, ip : %08X, prefixLength = %u\n", newFilter[i], filter[i], prefixLength);

        prefixLength -= 64;
        i++;
    }
    
    //printf("newFilter : %08X mask : %08X\n", newFilter[i], ((one << prefixLength) - 1));
    newFilter[i] = filter[i] & (((one << (64 - prefixLength)) - 1));
    printf("\tnewFilter : %08X, ip : %08X, prefixLength = %u\n", newFilter[i], filter[i], prefixLength);

    printf("newFilter :    \t");
    i = 0;
    for(i = 0; i < 2; i++)
    {
        printf("%08X ", newFilter[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");

    if(memcmp(newFilter, newIp, 16) == 0)
    {
        printf("Both IPv6 are in same subnet\n");
    }
    else
    {
        printf("Both IPv6 are in NOT same subnet\n");
    }
}
