#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>

#define VCM_IPV4_ADDR                           "%u.%u.%u.%u"
#define VCM_IPV4_ADDR_FORMAT(__addr)            (uint8_t)((__addr) & 0x000000ff),         \
                                                (uint8_t)(((__addr) & 0x0000ff00) >> 8 ), \
                                                (uint8_t)(((__addr) & 0x00ff0000) >> 16), \
                                                (uint8_t)(((__addr) & 0xff000000) >> 24)


#define VCM_IPV4_ADDR_FORMATP(__paddr)          (uint8_t)(*((uint8_t*)(__paddr)) & 0x000000ff),     \
                                                (uint8_t)(*((uint8_t*)(__paddr + 1)) & 0x000000ff), \
                                                (uint8_t)(*((uint8_t*)(__paddr + 2)) & 0x000000ff), \
                                                (uint8_t)(*((uint8_t*)(__paddr + 3)) & 0x000000ff)

#define VCM_IPV6_ADDR                           "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x:"\
                                                "%.2x%.2x"

#define VCM_IPV6_ADDR_FORMATP(__paddr)   \
                                            (uint8_t)(*((uint8_t*)(__paddr + 0)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 1)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 2)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 3)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 4)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 5)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 6)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 7)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 8)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 9)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 10)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 11)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 12)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 13)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 14)) & 0x000000ff), \
                                            (uint8_t)(*((uint8_t*)(__paddr + 15)) & 0x000000ff)

int areIpv4InSameSubnet(uint8_t* ipv4, uint8_t* ipv4Filter, uint8_t* ipv4Mask)
{
    uint8_t maskedIpv4Addr[4]         = {0};
    uint8_t maskedFilterIpv4Addr[4]   = {0};

    /* Mask IPv4 Addr */
    uint8_t i = 0;
    for(i=0; i < 4; i++)
    {
        maskedIpv4Addr[i] = ipv4[i] & ipv4Mask[i];
    }

    /* Mask FilterIPv4 Addr */
    i = 0;
    for(i=0; i < 4; i++)
    {
        maskedFilterIpv4Addr[i] = ipv4Filter[i] & ipv4Mask[i];
    }

    if(memcmp(maskedIpv4Addr, maskedFilterIpv4Addr, 4) == 0)
    {
        printf("\tmatched \n");
        return 1;
    }

    printf("\tnot matched \n");
    return 0;
}


int areIpv6InSameSubnet(uint8_t* ipv6, uint8_t* ipv6Filter, uint8_t* ipv6Mask)
{
    uint8_t maskedIpv6Addr[16]         = {0};
    uint8_t maskedFilterIpv6Addr[16]   = {0};

    /* Mask IPv6 Addr */
    uint8_t i = 0;
    for(i=0; i < 16; i++)
    {
        maskedIpv6Addr[i] = ipv6[i] & ipv6Mask[i];
    }

    /* Mask FilterIPv4 Addr */
    i = 0;
    for(i=0; i < 16; i++)
    {
        maskedFilterIpv6Addr[i] = ipv6Filter[i] & ipv6Mask[i];
    }

    if(memcmp(maskedIpv6Addr, maskedFilterIpv6Addr, 16) == 0)
    {
        printf("\tmatched \n");
        return 1;
    }

    printf("\tnot matched \n");
    return 0;
}

int areIpv6InSameSubnet2(uint8_t* ipv6Addr, uint8_t* filterIpv6Addr, uint32_t aPrefixLen)
{
    uint64_t maskedIpv6Addr[2]         = {0};
    uint16_t maskedFilterIpv6Addr[2]   = {0};

    uint32_t prefixLen = aPrefixLen;
    uint64_t one = 1;

    /* Mask IPv6 Addr */
    uint32_t i = 0;
    while(prefixLen >= 64)
    {
        maskedIpv6Addr[i] = ipv6Addr[i];
        prefixLen -= 64;
        i++;
    }
    maskedIpv6Addr[i] = (ipv6Addr[i] & ((one << (64 - prefixLen)) - 1));

    /* Mask FilterIPv6 Addr */
    prefixLen = aPrefixLen;
    i = 0;
    while(prefixLen >= 64)
    {
        maskedFilterIpv6Addr[i] = filterIpv6Addr[i];
        prefixLen -= 64;
        i++;
    }
    maskedFilterIpv6Addr[i] = (filterIpv6Addr[i] & ((one << (64 - prefixLen)) - 1));

    if(memcmp(maskedIpv6Addr, maskedFilterIpv6Addr, 16) == 0)
    {
        return 1;
    }

    return 0;
}


void
convert_ipv6_cidr_to_netmask(uint32_t aCidr, uint8_t *apNetmask)
{
    uint32_t cidr = aCidr;
    uint32_t i = 0;
    uint8_t  one = 1;

    while(cidr >= 8)
    {
        apNetmask[i] |= 0xFF;

        cidr -= 8;
        i++;
        printf(VCM_IPV6_ADDR"\n", 
                VCM_IPV6_ADDR_FORMATP(apNetmask));
    }

    apNetmask[i] = ~(((one << (8 - cidr)) - 1));
    printf(VCM_IPV6_ADDR"\n", 
                VCM_IPV6_ADDR_FORMATP(apNetmask));

}

int main()
{
    /* match IPv4 */
    uint8_t ipv4FilterStr[20] = {0}; 
    uint8_t ipv4MaskStr[20] = {0}; 
    uint8_t ipv4Str[20] = {0};

    uint8_t ipv4Filter[4] = {0};
    uint8_t ipv4Mask[4] = {0};
    uint8_t ipv4[4] = {0};

    strcpy(ipv4FilterStr, "192.168.11.4");
    strcpy(ipv4MaskStr, "255.255.255.0");
    strcpy(ipv4Str, "192.168.11.5");

    inet_pton(AF_INET, ipv4FilterStr, ipv4Filter);
    inet_pton(AF_INET, ipv4MaskStr, ipv4Mask);
    inet_pton(AF_INET, ipv4Str, ipv4);
    
    printf("Filter : "VCM_IPV4_ADDR", IPv4 : "VCM_IPV4_ADDR"\n", 
            VCM_IPV4_ADDR_FORMATP(ipv4Filter), VCM_IPV4_ADDR_FORMATP(ipv4));

    areIpv4InSameSubnet(ipv4, ipv4Filter, ipv4Mask);
    
    /* match IPv6 */
    uint8_t ipv6FilterStr[40] = {0}; 
    uint8_t ipv6MaskStr[40] = {0}; 
    uint8_t ipv6Str[40] = {0};

    uint8_t ipv6Filter[16] = {0};
    uint8_t ipv6Mask[16] = {0};
    uint8_t ipv6[16] = {0};

    strcpy(ipv6FilterStr, "2001:11:12:13:14:12:12:11");
    strcpy(ipv6MaskStr, "FFFF:FFFF:FFFF:FFFF:FFFD:0:0:0");
    strcpy(ipv6Str, "2001:11:12:13:14:1:1:111");

    inet_pton(AF_INET6, ipv6FilterStr, ipv6Filter);
    inet_pton(AF_INET6, ipv6MaskStr, ipv6Mask);
    inet_pton(AF_INET6, ipv6Str, ipv6);

    printf("Filter : "VCM_IPV6_ADDR", IPv6 : "VCM_IPV6_ADDR"\n", 
            VCM_IPV6_ADDR_FORMATP(ipv6Filter), VCM_IPV6_ADDR_FORMATP(ipv6));

    areIpv6InSameSubnet(ipv6, ipv6Filter, ipv6Mask);

    uint8_t cidr = 63;
    uint8_t ipv6NetMask[16] = {0};

    convert_ipv6_cidr_to_netmask(cidr, ipv6NetMask);

    printf("IPv6 :: "VCM_IPV6_ADDR"\n",
            VCM_IPV6_ADDR_FORMATP(ipv6NetMask));
}
