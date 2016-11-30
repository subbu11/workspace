#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct IpAddrS
{
    int length;
    uint8_t value[20];
} IpAddrT;



#define VCM_IPV4_ADDR                           "%u.%u.%u.%u"
#define VCM_IPV4_ADDR_FORMAT(__addr)            (uint8_t)((__addr) & 0x000000ff),         \
    (uint8_t)(((__addr) & 0x0000ff00) >> 8 ), \
(uint8_t)(((__addr) & 0x00ff0000) >> 16), \
(uint8_t)(((__addr) & 0xff000000) >> 24)

#define VCM_IPV4_ADDR_FORMATP(__paddr)          (uint8_t)(*((uint8_t*)(__paddr))     & 255), \
                                                (uint8_t)(*((uint8_t*)(__paddr + 1)) & 255), \
                                                (uint8_t)(*((uint8_t*)(__paddr + 2)) & 255), \
                                                (uint8_t)(*((uint8_t*)(__paddr + 3)) & 255)


#define VCM_IPV6_PREFIX                         "%04X:%04X:%04X:%04X"

#define VCM_IPV6_PREFIX_FORMATP(__paddr)        (uint16_t)(*((uint16_t*)(__paddr))     & 65535), \
                                                (uint16_t)(*((uint16_t*)(__paddr + 2)) & 65535), \
(uint16_t)(*((uint16_t*)(__paddr + 4)) & 65535), \
(uint16_t)(*((uint16_t*)(__paddr + 6)) & 65535)

#define VCM_IPV6_ADDR_1                            "%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X"

#define VCM_IPV6_ADDR_FORMATP_1(__paddr)           (uint8_t)(*((uint8_t*)(__paddr))      & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 1))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 2))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 3))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 4))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 5))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 6))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 7))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 8))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 9))  & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 10)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 11)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 12)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 13)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 14)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 15)) & 255)

#define VCM_IPV6_PREFIX_1                          "%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X"

#define VCM_IPV6_PREFIX_FORMATP_1(__paddr)         (uint8_t)(*((uint8_t*)(__paddr))     & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 1)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 2)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 3)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 4)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 5)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 6)) & 255), \
(uint8_t)(*((uint8_t*)(__paddr + 7)) & 255)

 
static uint64_t vcmIpMgrIpv6PoolConvertIpv6StrToU64(uint8_t* aPrefixStr)
{
    uint64_t prefix = 0;
    char *token = NULL;

    token = strtok((char*)aPrefixStr, ":");

    uint64_t index = 0;
    while(token != NULL)
    {
        uint64_t number = (uint64_t)strtol(token, NULL, 16);

        prefix |= (number << (64 - (16 * (index + 1))));

        token = strtok(NULL, ":");

        index++;
    }

    uint8_t *p = &prefix;
    printf("IPv6 Prefix : 0x%016llX  "VCM_IPV6_PREFIX_1"\n", 
            prefix, VCM_IPV6_PREFIX_FORMATP_1(p));

    return prefix;
}


int isIpv6PrefixValid(uint64_t ipv6Prefix)
{
    struct sockaddr_in6 addr;

    printf("Prefix : %016llX\n", ipv6Prefix);

    uint64_t intfId = 0;

    uint8_t ipv6Addr[16] = {0};
    memcpy(ipv6Addr, &ipv6Prefix, 8);
    memcpy(&ipv6Addr[8], &intfId, 8);

    addr.sin6_family = AF_INET6;
    memcpy(addr.sin6_addr.s6_addr, ipv6Addr, 16);

    if (IN6_IS_ADDR_UNSPECIFIED(&addr.sin6_addr))
    {
        printf("Unspecified\n");
        return 0;
    }
    else if (IN6_IS_ADDR_LOOPBACK(&addr.sin6_addr)) 
    {
        printf("Loopback\n");
        return 0;
    }
    else if(IN6_IS_ADDR_MULTICAST(&addr.sin6_addr))
    {
        printf("Multicast\n");
        return 0;
    }
    else if(IN6_IS_ADDR_LINKLOCAL(&addr.sin6_addr))
    {
        printf("Link local\n");
        return 0;
    }
    else
    {
        printf("Global\n");
        return 1;
    }
}


int
main(int argc, char *argv[])
{
    unsigned char buf[sizeof(struct in6_addr)];
    int domain, s;
    char str[INET6_ADDRSTRLEN];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s {i4|i6|<num>} string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    domain = (strcmp(argv[1], "i4") == 0) ? AF_INET :
        (strcmp(argv[1], "i6") == 0) ? AF_INET6 : atoi(argv[1]);

    
    printf("------- %s\n", argv[2]);
    s = inet_pton(domain, argv[2], buf);
    if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format : %s\n", argv[2]);
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    
    }
/*
    printf("IPv6 : "VCM_IPV6_ADDR_1"\n", VCM_IPV6_ADDR_FORMATP_1(buf));
if(domain == AF_INET6)
    {
        uint64_t p  = vcmIpMgrIpv6PoolConvertIpv6StrToU64(argv[2]);
    }*/


    IpAddrT ip;
    
    s = inet_pton(AF_INET, "192.168.10.10", &ip.value[0]);
    if(s <= 0)
    {
        printf("\n IPv4 Error \n");
    }
    else 
    {
        printf("\n IPv4 : "VCM_IPV4_ADDR, VCM_IPV4_ADDR_FORMATP(&ip.value[0]));
    }

    s = inet_pton(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888", &ip.value[4]);
    if(s <= 0)
    {
        printf("\n IPv6 Error \n");
    }
    else 
    {
        printf("\n IPv6 : "VCM_IPV6_PREFIX, VCM_IPV6_PREFIX_FORMATP(&ip.value[4]));
        printf("\n IPv6 : "VCM_IPV6_PREFIX_1, VCM_IPV6_PREFIX_FORMATP_1(&ip.value[4]));
    }
    if(domain == AF_INET)
    {
        struct in_addr addr;
        if(inet_aton(argv[2], &addr) == 0)
        {
            printf("Error : Invalid Address\n");
        }
        else 
        {
          printf("\n inet_aton : 0x%X\n", addr);
        }
    }
    
    printf("------- %s\n", argv[2]);
    s = inet_pton(domain, argv[2], buf);
    if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format : %s\n", argv[2]);
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    char new[40];
    inet_ntop(domain, buf, new, INET6_ADDRSTRLEN);

    printf("\nNEW STRING :::::: %s\n", new);

    if(domain == AF_INET)
    {
        uint32_t ip = 0;
        memcpy(&ip, buf, 4);

        printf("IPv4 : 0x%X", ip);
    }
    else if(domain == AF_INET6)
    {
        uint8_t *pBuf8 = buf;
        uint16_t *pBuf16 = buf;
        uint32_t *pBuf32 = buf;
        uint64_t *pBuf64 = buf;

        printf("prefix : "VCM_IPV6_PREFIX"\n", VCM_IPV6_PREFIX_FORMATP(pBuf8));
        printf("prefix : "VCM_IPV6_PREFIX"\n", VCM_IPV6_PREFIX_FORMATP(pBuf16));
        printf("prefix : "VCM_IPV6_PREFIX"\n", VCM_IPV6_PREFIX_FORMATP(pBuf32));
        printf("prefix : "VCM_IPV6_PREFIX"\n", VCM_IPV6_PREFIX_FORMATP(pBuf64));

        printf("--------- prefix   : "VCM_IPV6_PREFIX"\n", VCM_IPV6_PREFIX_FORMATP(pBuf8));
        printf("--------- prefix-1 : "VCM_IPV6_PREFIX_1"\n", VCM_IPV6_PREFIX_FORMATP_1(pBuf8));
        
        printf("--------- addr-1  : "VCM_IPV6_ADDR_1"\n", VCM_IPV6_ADDR_FORMATP_1(pBuf8));


        uint64_t ipv6Prefix = 0;
        memcpy(&ipv6Prefix, buf, 8);
        
        if(isIpv6PrefixValid(ipv6Prefix))
        {
            printf("GLOBAL UNICAST\n");
        }
        else
        {
            printf("NOT GLOBAL UNICAST\n");
        }

        uint64_t* ptr = (uint64_t *) buf;
        ptr = ptr + 1;

        uint64_t ipv6IntfId = 0;
        memcpy(&ipv6IntfId, ptr, 8);
        printf("IPv6 : prefix : 0x%llX interface : 0x%llX\n", ipv6Prefix, ipv6IntfId);

        int i;
        for(i = 0; i < sizeof(struct in6_addr); i++)
        {
            printf("i : %u char : %c int : %u hex : '%X'\n", i, buf[i], buf[i], buf[i]);
        }
    }

    if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", str);

    exit(EXIT_SUCCESS);
}
