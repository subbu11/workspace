nclude <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()

#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_TCP, INET6_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <netinet/ip6.h>      // struct ip6_hdr
#define __FAVOR_BSD           // Use BSD format of tcp header
#include <netinet/tcp.h>      // struct tcphdr
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_IP = 0x0800, ETH_P_IPV6 = 0x86DD
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>

#include <errno.h>            // errno, perror()
void ipv6_to_str_unexpanded(char *str, const struct in6_addr * addr) 
{
    sprintf(str, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            (int)addr->s6_addr[0], (int)addr->s6_addr[1],
            (int)addr->s6_addr[2], (int)addr->s6_addr[3],
            (int)addr->s6_addr[4], (int)addr->s6_addr[5],
            (int)addr->s6_addr[6], (int)addr->s6_addr[7],
            (int)addr->s6_addr[8], (int)addr->s6_addr[9],
            (int)addr->s6_addr[10], (int)addr->s6_addr[11],
            (int)addr->s6_addr[12], (int)addr->s6_addr[13],
            (int)addr->s6_addr[14], (int)addr->s6_addr[15]);
    printf("addr:[%s]\n",str);
}


static inline uint16_t
get_16b_sum(uint16_t *ptr16, uint32_t nr)
{
    uint32_t sum = 0;
    while (nr > 1)
    {
        sum +=*ptr16;
        nr -= sizeof(uint16_t);
        ptr16++;
        if (sum > UINT16_MAX)
            sum -= UINT16_MAX;
    }

    /* If length is in odd bytes */
    if (nr)
        sum += *((uint8_t*)ptr16);

    sum = ((sum & 0xffff0000) >> 16) + (sum & 0xffff);
    sum &= 0x0ffff;
    return (uint16_t)sum;
}

static inline uint16_t 
get_ipv6_psd_sum (struct ip6_hdr * ip_hdr)
{
    /* Pseudo Header for IPv6/UDP/TCP checksum */
    union ipv6_psd_header {
        struct {
            uint8_t src_addr[16]; /* IP address of source host. */
            uint8_t dst_addr[16]; /* IP address of destination host(s). */
            uint32_t len;         /* L4 length. */
            uint32_t proto;       /* L4 protocol - top 3 bytes must be zero */
        } __attribute__((__packed__));

        uint16_t u16_arr[0]; /* allow use as 16-bit values with safe aliasing */
    } psd_hdr;

    memcpy(&psd_hdr.src_addr, &ip_hdr->ip6_src,
            (sizeof(ip_hdr->ip6_src) + sizeof(ip_hdr->ip6_dst)));
    //psd_hdr.len       = ip_hdr->payload_len;
    psd_hdr.len       = ip_hdr->ip6_plen;
    psd_hdr.proto     = IPPROTO_TCP;//(ip_hdr->proto << 24);

    return get_16b_sum(psd_hdr.u16_arr, sizeof(psd_hdr));
}

static inline uint16_t 
get_ipv6_udptcp_checksum(struct ip6_hdr *ipv6_hdr, uint16_t *l4_hdr)
{
    uint32_t cksum;
    uint32_t l4_len;

    l4_len = (ipv6_hdr->ip6_plen);

    cksum = get_16b_sum(l4_hdr, l4_len);
    cksum += get_ipv6_psd_sum(ipv6_hdr);

    cksum = ((cksum & 0xffff0000) >> 16) + (cksum & 0xffff);
    cksum = (~cksum) & 0xffff;
    if (cksum == 0)
        cksum = 0xffff;

    return (uint16_t)cksum;
}

//! \brief Calculate the TCP checksum.
////! \param buff The TCP packet.
////! \param len The size of the TCP packet.
////! \param src_addr The IP source address (in network format).
////! \param dest_addr The IP destination address (in network format).
////! \return The result of the checksum.
uint16_t tcp_checksum(const void *buff, size_t len, struct in6_addr src_addr, struct in6_addr dest_addr)
{
    const uint16_t *buf=buff;
    uint16_t *ip_src=(void *)&src_addr, *ip_dst=(void *)&dest_addr;
    uint32_t sum;
    size_t length=len;

    // Calculate the sum
    sum = 0;
    while (len > 1)
    {
        sum += *buf++;
        if (sum & 0x80000000)
            sum = (sum & 0xFFFF) + (sum >> 16);
        len -= 2;
    }

    if ( len & 1 )
        // Add the padding if the packet lenght is odd
        sum += *((uint8_t *)buf);

    // Add the pseudo-header
    sum += *(ip_src++);
    sum += *ip_src;
    sum += *(ip_dst++);
    sum += *ip_dst;
    sum += htons(IPPROTO_TCP);
    sum += htons(length);

    // Add the carries   
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    // Return the one's complement of sum
    return ( (uint16_t)(~sum)  );
}

// Define some constants.
#define ETH_HDRLEN 14  // Ethernet header length
#define IP6_HDRLEN 40  // IPv6 header length
#define TCP_HDRLEN 20  // TCP header length, excludes options data

// Function prototypes
int16_t checksum (uint16_t *, int);
uint16_t tcp6_checksum (struct ip6_hdr, struct tcphdr, uint8_t *, int);
char *allocate_strmem (int);
uint8_t *allocate_ustrmem (int);
int *allocate_intmem (int);

int
main (int argc, char **argv)
{
    int i, status, frame_length, sd, bytes, *tcp_flags, opt_len;
    char *interface, *target, *src_ip, *dst_ip;
    struct ip6_hdr iphdr;
    struct tcphdr tcphdr;
    uint8_t *src_mac, *dst_mac, *ether_frame;
    uint8_t *options;
    struct addrinfo hints, *res;
    struct sockaddr_in6 *ipv6;
    struct sockaddr_ll device;
    struct ifreq ifr;
    void *tmp;

    // Allocate memory for various arrays.
    src_mac = allocate_ustrmem (6);
    dst_mac = allocate_ustrmem (6);
    ether_frame = allocate_ustrmem (IP_MAXPACKET);
    interface = allocate_strmem (40);
    target = allocate_strmem (INET6_ADDRSTRLEN);
    src_ip = allocate_strmem (INET6_ADDRSTRLEN);
    dst_ip = allocate_strmem (INET6_ADDRSTRLEN);
    tcp_flags = allocate_intmem (8);
    options = allocate_ustrmem (40);

    // Interface to send packet through.
    strcpy (interface, "eth0");

    // Source IPv6 address: you need to fill this out
    strcpy (src_ip,"1080:a2b1::1e:0");
    strcpy (dst_ip,"ff00::24");

    // IPv6 header
    iphdr.ip6_flow = htonl ((6 << 28) | (0 << 20) | 0);


    // Payload length (16 bits): TCP header + TCP options
    //   //iphdr.ip6_plen = htons (TCP_HDRLEN + opt_len);
    //     //iphdr.ip6_plen = htons (TCP_HDRLEN);


    iphdr.ip6_plen = htons(TCP_HDRLEN);

    iphdr.ip6_nxt = IPPROTO_TCP;

    iphdr.ip6_hops = 128;

    // Source IPv6 address (128 bits)
    if ((status = inet_pton (AF_INET6, src_ip, &(iphdr.ip6_src))) != 1) {
        fprintf (stderr, "inet_pton() failed.\nError message: %s", strerror (status));
        exit (EXIT_FAILURE);
    }

    char srcAddr[32];
    memset(srcAddr,0,32);
    printf("src ip addr:");
    ipv6_to_str_unexpanded(srcAddr,&(iphdr.ip6_src));

    if ((status = inet_pton (AF_INET6, dst_ip, &(iphdr.ip6_dst))) != 1) {
        fprintf (stderr, "inet_pton() failed.\nError message: %s", strerror (status));
        exit (EXIT_FAILURE);
    }
    char dstAddr[32];
    memset(dstAddr,0,32);
    printf("dst ip addr:");
    ipv6_to_str_unexpanded(dstAddr,&(iphdr.ip6_dst));

    tcp_flags[7] = 0;

    tcphdr.th_flags = 0;
    for (i=0; i<8; i++) {
        tcphdr.th_flags += (tcp_flags[i] << i);
    }

    tcphdr.th_sport = htons (1058);
    printf("src port:[%d]\n",tcphdr.th_sport);

    tcphdr.th_dport = htons (80);
    tcphdr.th_seq = htonl (1);
    printf("seq :[%d]\n",tcphdr.th_seq);

    tcphdr.th_ack = htonl (1);
    tcphdr.th_x2 = 0;

    // Data offset (4 bits): size of TCP header + length of options, in 32-bit words
    //   //tcphdr.th_off = (TCP_HDRLEN + opt_len) / 4;
    tcphdr.th_off = TCP_HDRLEN/4;

    // Flags (8 bits)
    // FIN flag (1 bit)
    tcp_flags[0] = 0;
    // SYN flag (1 bit): set to 1
    tcp_flags[1] = 0;
    // RST flag (1 bit)
    tcp_flags[2] = 1;

    // PSH flag (1 bit)
    tcp_flags[3] = 0;

    // ACK flag (1 bit)
    tcp_flags[4] = 1;

    // URG flag (1 bit)
    tcp_flags[5] = 0;

    // ECE flag (1 bit)
    tcp_flags[6] = 0;

    // CWR flag (1 bit)
    tcp_flags[7] = 0;

    tcphdr.th_flags = 0;
    for (i=0; i<8; i++) {
        tcphdr.th_flags += (tcp_flags[i] << i);
    }

    // Window size (16 bits)
    tcphdr.th_win = htons (8760);

    // Urgent pointer (16 bits): 0 (only valid if URG flag is set)
    tcphdr.th_urp = htons (0);

    tcphdr.th_sum  = 0;

    tcphdr.th_sum = tcp_checksum((void *)&tcphdr, htons(20), iphdr.ip6_src, iphdr.ip6_dst);

    printf("TCP Checksum:[%x]\n",tcphdr.th_sum);

    return 0;
}

char *
allocate_strmem (int len)
{
    void *tmp;

    if (len <= 0) {
        fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_strmem().\n", len);
        exit (EXIT_FAILURE);
    }

    tmp = (char *) malloc (len * sizeof (char));
    if (tmp != NULL) {
        memset (tmp, 0, len * sizeof (char));
        return (tmp);
    } else {
        fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_strmem().\n");
        exit (EXIT_FAILURE);
    }
}

