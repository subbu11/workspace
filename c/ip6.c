#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <stdlib.h>

#if defined(__linux__)
#  include <endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__)
#  include <sys/endian.h>
#elif defined(__OpenBSD__)
#  include <sys/types.h>
#  define be16toh(x) betoh16(x)
#  define be32toh(x) betoh32(x)
#  define be64toh(x) betoh64(x)
#endif

#define TYP_INIT 0 
#define TYP_SMLE 1 
#define TYP_BIGE 2 

unsigned long long htonll(unsigned long long src) { 
    static int typ = TYP_INIT; 
    unsigned char c; 
    union { 
        unsigned long long ull; 
        unsigned char c[8]; 
    } x; 
    if (typ == TYP_INIT) { 
        x.ull = 0x01; 
        typ = (x.c[7] == 0x01ULL) ? TYP_BIGE : TYP_SMLE; 
    } 
    if (typ == TYP_BIGE) 
        return src; 
    x.ull = src; 
    c = x.c[0]; x.c[0] = x.c[7]; x.c[7] = c; 
    c = x.c[1]; x.c[1] = x.c[6]; x.c[6] = c; 
    c = x.c[2]; x.c[2] = x.c[5]; x.c[5] = c; 
    c = x.c[3]; x.c[3] = x.c[4]; x.c[4] = c; 
    return x.ull; 
}

int main(void) {

    uint64_t prefix = 0x4444333322221111;
    //uint64_t prefix = 0x1111222233334444;

    uint64_t one = 1;
    uint64_t tmp = ((one << 60) - 1);
    printf(" tmp  : 0x%016llX\n", tmp);

    uint64_t start = prefix & tmp;
    printf(" start : 0x%016llX %llu\n", start, start);

    uint64_t end = prefix | (~tmp);
    printf(" end : 0x%016llX %llu\n", end, end);

    uint64_t num = end - start + 1;
    printf("num : %llu\n", num);
    uint64_t start1 = be64toh(start);
    printf(" start1 : 0x%016llX %llu\n", start1, start1);
    uint64_t end1 = be64toh(end);
    printf(" end1 : 0x%016llX %llu\n", end1, end1);
    uint64_t num1 = be64toh(end) - be64toh(start);


    printf("num1 : %u\n", num1);
    num1 = end1 - start1;
    printf("num1 : %u\n", end1 - start1);


    uint64_t start2 = htonll(start);
    printf(" start1 : 0x%016llX %llu\n", start1, start1);
    uint64_t end2 = htonll(end);
    printf(" end1 : 0x%016llX %llu\n", end1, end1);
    uint64_t num2 = end2 - start2 ;
    printf("num2 : %u\n", num2);
    
    printf("---------- %llu\n", 0xF444333322221111 - 0x0444333322221111);
    printf("---------- %llu\n", 0x111122223333444F - 0x1111222233334440);

    uint8_t value[100];

    uint64_t s1 = 0;
    uint64_t s2 = 0;
    int rc = inet_pton(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888", value);
    if(rc <= 0)
    {
        printf("\n IPv6 Error \n");
    }
    else
    {
        //printf("\n IPv6 : "VCM_IPV6_PREFIX, VCM_IPV6_PREFIX_FORMATP(&ip.value[4]));

        memcpy(&s1, value, 8);
        printf("\n IPv6 : 0x%016llX\n", s1);
    }

    rc = inet_pton(AF_INET6, "1111:2222:3333:44F4:5555:6666:7777:8888", value);
    if(rc <= 0)
    {
        printf("\n IPv6 Error \n");
    }
    else
    {
        //printf("\n IPv6 : "VCM_IPV6_PREFIX, VCM_IPV6_PREFIX_FORMATP(&ip.value[4]));

        memcpy(&s2, value, 8);
        printf("\n IPv6 : 0x%016llX\n", s2);
    }
    printf(" s1 : %llX s2 : %llX\n", s1, s2);
    
    uint64_t n2 = be64toh(s2) - be64toh(s1) + 1; 
    printf("n2 : %llu \n", n2);

    /* IPv4 */
    uint32_t ip = inet_addr("192.168.11.80");
    printf("num : %X %u\n", ip);

    ip = inet_addr("192.0.0.0");
    printf("num : %X %u\n", ip);

    uint32_t s = inet_addr("192.168.110.11");
    printf("start : %X\n", s);

    uint32_t e  = inet_addr("192.168.110.22");
    printf("end : %X\n", e);

    uint32_t n = e - s + 1;
    uint32_t n1 = ntohl(e) - ntohl(s) + 1;

    printf("n : %u\n", n);
    printf("n1 : %u\n", n1);

    return 0;
}

