#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VCM_IPV6_PREFIX_1                          "%.2X%.2X:%.2X%.2X:%.2X%.2X:%.2X%.2X"

#define VCM_IPV6_PREFIX_FORMATP_1(__paddr)         (uint8_t)(*((uint8_t*)(__paddr))     & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 1)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 2)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 3)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 4)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 5)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 6)) & 255), \
    (uint8_t)(*((uint8_t*)(__paddr + 7)) & 255)


#define VCM_ntohll(x) (((uint64_t)(ntohl((uint32_t)((x << 32) >> 32))) << 32) | (uint32_t)ntohl(((uint32_t)(x >> 32))))

#define VCM_htonll(x) VCM_ntohll(x)


uint64_t vcmIpMgrIpv6PoolConvertIpv6StrToU64(char* aPrefixStr)
{
    uint64_t prefix = 0;
    char *token = NULL;
    
    printf("fdf\n");
    printf("String : %s\n", aPrefixStr);

    token = strtok((char*)aPrefixStr, ":");
    
    uint8_t ipv6Prefix[8];
    uint8_t i;

    uint64_t tokenIndex = 4;
    while(token != NULL)
    {
        uint64_t number = (uint64_t)strtol(token, NULL, 16);

        uint8_t *p;
        p = &number;
        
        memcpy(&ipv6Prefix[i++], p+1, 1);
        //printf("Copied %X at index=%u\n", *(p+1), i);

        memcpy(&ipv6Prefix[i++], p, 1);
        //printf("Copied %X at index=%u\n", *(p), i);

        //printf("token : 0x%016llX   ", number);

        //prefix |= (number << (64 - (16 * tokenIndex)));

        //printf("prefix : 0x%016llX\n", prefix);

        token = strtok(NULL, ":");

        tokenIndex--;
    }

    //uint8_t *p = &prefix;
    //printf("IPv6 Prefix : 0x%016llX  "VCM_IPV6_PREFIX_1"\n",
    //        prefix, VCM_IPV6_PREFIX_FORMATP_1(p)); 

    memcpy(&prefix, ipv6Prefix, 8);
    
    printf("Prefix Generated : 0x%016llX "VCM_IPV6_PREFIX_1"\n", prefix, VCM_IPV6_PREFIX_FORMATP_1(ipv6Prefix));

    return prefix;
}

uint64_t getStartingPrefix(uint64_t prefix)
{

}

uint64_t getEndingPrefix(uint64_t prefix)
{

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

    printf("argv : %s\n", argv[2]);
    s = inet_pton(domain, argv[2], buf);
    if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    else 
    {
        int num = 16;
        /* without function */
        uint64_t prefix;
        uint8_t *p = &prefix;
        memcpy(&prefix, buf, 8);

        printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", prefix, VCM_IPV6_PREFIX_FORMATP_1(p));
        
        printf("\nWhat will be IPv6 Prefixes if the standard inet-pton is used\n");
        int i = 0;
        for(i = 0; i < num; i++)
        {
            uint64_t pr = prefix + i;
            p = &pr;
            printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", pr, VCM_IPV6_PREFIX_FORMATP_1(p));
        }

        printf("\n REVERSE ::What will be IPv6 Prefixes if the standard inet-pton is used\n");
        uint64_t prefix2;
        uint8_t *p2 = &prefix2;
        prefix2 = VCM_ntohll(prefix);
        printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", prefix2, VCM_IPV6_PREFIX_FORMATP_1(p2));
        for(i = 0; i < num; i++)
        {
            uint64_t pr = prefix2 + i;
            p = &pr;
            printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", pr, VCM_IPV6_PREFIX_FORMATP_1(p));
        }
        printf("\n");

        uint64_t tmp = 0x7654321987654321;
        uint8_t *t = &tmp;
        printf("Tmp : 0x%016llX "VCM_IPV6_PREFIX_1"\n", tmp, VCM_IPV6_PREFIX_FORMATP_1(t));

        uint64_t tmp2 = VCM_ntohll(tmp);
        t = &tmp2;
        printf("Tmp : 0x%016llX "VCM_IPV6_PREFIX_1"\n", tmp2, VCM_IPV6_PREFIX_FORMATP_1(t));

        uint8_t aPrefixLength = 60;

        //uint64_t start = prefix & (~((1 << (64 - aPrefixLength)) - 1));
        //uint64_t end   = prefix | ((1 << (64 - aPrefixLength)) - 1);
        
        uint64_t one = 1;
        uint64_t start = prefix & ((one << aPrefixLength) - 1);
        uint64_t end   = prefix | (~((one << aPrefixLength) - 1));

        num = end - start + 1;
        p = &start;
        printf("Start : 0x%016llX "VCM_IPV6_PREFIX_1"\n", start, VCM_IPV6_PREFIX_FORMATP_1(p));
        p = &end;
        printf("End : 0x%016llX "VCM_IPV6_PREFIX_1"\n", end, VCM_IPV6_PREFIX_FORMATP_1(p));
        printf("Num : %u\n", num);
         
        for(i = 0; i < num; i++)
        {
            uint64_t pr = prefix + i;
            p = &pr;
            printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", pr, VCM_IPV6_PREFIX_FORMATP_1(p));
        }

#if 1
        /* with function */
        char *s1 = "1234:5678:9123:4567";
        char s[100];
        strcpy(s, s1);
        prefix = vcmIpMgrIpv6PoolConvertIpv6StrToU64(s);
        p = &prefix;
        printf("With Our Function : Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", prefix, VCM_IPV6_PREFIX_FORMATP_1(p));
#endif


        printf("\nHow IPv6 Prefixes should look like \n");
        
        //uint64_t sIp = 0x6745239178563402;
        uint64_t sIp = 0x1234567891234560;
        //uint64_t eIp = 0x67452391785634f2;
        uint64_t eIp = 0x123456789123456F;

        int numIp =  eIp - sIp + 1;
        printf("\n num : %u\n", numIp);
        for(i=0; i< 16; i++)
        {
#if 0
            uint64_t tmpIp = VCM_ntohll(sIp); 
            uint64_t t = tmpIp + i;
            uint8_t *psIp = &t;
            printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", t, VCM_IPV6_PREFIX_FORMATP_1(psIp));
#endif
            //uint64_t tmpIp = VCM_ntohsIp); 
            uint64_t t = sIp + i;
            uint8_t *psIp = &t;
            uint64_t tmpIp = VCM_ntohll(t); 
            uint8_t *pt = &tmpIp;
            printf("Prefix : 0x%016llX "VCM_IPV6_PREFIX_1"\n", t, VCM_IPV6_PREFIX_FORMATP_1(pt));
        }

        printf("");
    }

    if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", str);

    exit(EXIT_SUCCESS);
}
