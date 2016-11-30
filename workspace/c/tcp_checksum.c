#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define VCM_DPE_HTTP_SIZE_OF_IP_HEADER       (20)
#define VCM_DPE_HTTP_SIZE_OF_TCP_HEADER      (20)

typedef struct Ipv4HeaderS {
#if BYTE_ORDER == LITTLE_ENDIAN
    uint32_t     ihl:4,          /* header length */
                version:4;      /* version */
#else
    uint32_t     version:4,      /* version */
                ihl:4;          /* header length */
#endif
    uint8_t      tos;            /* type of service */
    uint16_t     length;        /* total length */
    uint16_t     id;             /* identification */
    uint16_t     frag_off;       /* fragment offset field */
    uint8_t      ttl;            /* time to live */
    uint8_t      protocol;       /* protocol */
    uint16_t     check;          /* checksum */
    uint32_t     saddr;          /* source address */
    uint32_t     daddr;          /* dest address */
} Ipv4HeaderT;

#define VCM_DPE_HTTP_SIZE_OF_IPV6_FIXED_HEADER       (40)

typedef struct Ipv6HeaderS
{
    uint32_t            v_tc_fl;
    uint16_t            payload_len;
    uint8_t             nexthdr;
    uint8_t             hop_limit;

    struct in6_addr    saddr;
    struct in6_addr    daddr;
} Ipv6HeaderT;

typedef struct TcpHeaderS {
    uint16_t     srcPort;
    uint16_t     dstPort;
    uint32_t     seq;
    uint32_t     ack;
#if 0
    uint16_t     flags;
#endif
    uint8_t      dataOffset;
    uint8_t      flags;
    uint16_t     windowSize;;
    uint16_t     csum;
    uint16_t     urg;
} TcpHeaderT;

typedef struct TcpPseudoHeaderS {
    uint32_t     saddr;          /* source address */
    uint32_t     daddr;          /* dest address */
    uint8_t      reserved;
    uint8_t      protocol;       /* protocol */
    uint16_t     length;
} TcpPseudoHeaderT;

typedef struct TcpPseudoHeaderIpv6S
{
    struct in6_addr saddr;
    struct in6_addr daddr;
    uint16_t    length;
#if BYTE_ORDER == LITTLE_ENDIAN
    uint8_t     reserved[3];
    uint8_t     nexthdr;
#else
    uint8_t     nexthdr;
    uint8_t     reserved[3];
#endif

} TcpPseudoHeaderIpv6T;

unsigned short vcmDpeHttpTcpCsum(unsigned short *buf, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = buf;
    register int nleft = len;

    /*
     *      * * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     *           * * sequential 16 bit words to it, and at the end, fold back all the
     *                * * carry bits from the top 16 bits into the lower 16 bits.
     *                     * */
    while (nleft > 1)  {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)w ;
        sum += answer;
    }

    //while(sum >> 16)
    //{
        sum = (sum >> 16) + (sum & 0xffff);
    //}

    sum += (sum >> 16);

    answer = ~sum;
    return(answer);
}

void calcTcpCsumIpv6(Ipv6HeaderT*  pIpv6Header)
{
    uint8_t tcpCsumBlock[4096];
    memset(tcpCsumBlock, 0, 4096);

    TcpPseudoHeaderIpv6T tcpPseudoHdr;
    TcpHeaderT  *pTcpHeader = (TcpHeaderT*)((uint8_t*)pIpv6Header + VCM_DPE_HTTP_SIZE_OF_IPV6_FIXED_HEADER);

    tcpPseudoHdr.saddr    = pIpv6Header->saddr;
    tcpPseudoHdr.daddr    = pIpv6Header->daddr;
    tcpPseudoHdr.reserved[0] = 0x00;
    tcpPseudoHdr.reserved[1] = 0x00;
    tcpPseudoHdr.reserved[2] = 0x00;
    tcpPseudoHdr.nexthdr = pIpv6Header->nexthdr;
    tcpPseudoHdr.length  = pIpv6Header->payload_len;

    pTcpHeader->csum      = 0x0000;

    memcpy(tcpCsumBlock, &tcpPseudoHdr, sizeof(TcpPseudoHeaderIpv6T));
    memcpy(tcpCsumBlock + sizeof(TcpPseudoHeaderIpv6T), pTcpHeader, ntohs(tcpPseudoHdr.length));

    pTcpHeader->csum = vcmDpeHttpTcpCsum((unsigned short *)tcpCsumBlock, (sizeof(TcpPseudoHeaderIpv6T) + ntohs(tcpPseudoHdr.length)));

    printf("TCP Checksum :::::: %04X\n\n", pTcpHeader->csum);
}

int main()
{
    uint8_t buf[4096] = {
                        0x60, 0x00, 0x00, 0x00, 0x00, 0x27, 0x06, 0x40,   0x20, 0x01, 0x00, 0x10, 0x01, 0x76, 0x01, 0x00, 
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x00, 0x11, 0x00, 0x11, 0x00, 0x01, 0x00, 0x0d, 
                        0x01, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76,
                        0x00, 0x50, 0x07, 0xd0, 0x07, 0x4e, 0x9a, 0xa2,   0x07, 0x6d, 0x31, 0xbf, 0x50, 0x18, 0x80, 0x00,
                        0x81, 0x5f, 0x00, 0x00,
                        0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31,   0x20, 0x32, 0x30, 0x30, 0x20, 0x4f, 0x4b, 0x0d,
                        0x0a, 0x0d, 0x0a
                        };
    Ipv6HeaderT* pIpv6 = (Ipv6HeaderT*)buf;
    
    calcTcpCsumIpv6(pIpv6);
}
