/*
 * Listening all packets received on ethernet raw socket 
 *
 */
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <sys/select.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h> // IFNAMSIZ
#include <netinet/ether.h>
#include <linux/if_packet.h>
#include <sys/ioctl.h>


void print_ethernet_header(unsigned char* Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;

    printf("\n");
    //printf("Ethernet Header\n"); 
    
    char hwAddr[100] = {0};
    sprintf(hwAddr, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", 
    eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );

    if(strcmp(hwAddr, "00-0C-29-76-1D-C8") == 0)
    {
        printf("Packet being sent by interface eth0\n");
    }
    else if(strcmp(hwAddr, "00-0C-29-76-1D-D2") == 0)
    {
        printf("Packet being sent by interface eth1\n");
    }
    else if(strcmp(hwAddr, "00-0C-29-76-1D-DC") == 0)
    {
        printf("Packet being sent by interface eth2\n");
    }
    
    memset(hwAddr, 0, 100);
    sprintf(hwAddr, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", 
    eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );

    if(strcmp(hwAddr, "00-0C-29-76-1D-C8") == 0)
    {
        printf("Packet being received by interface eth0\n");
    }
    else if(strcmp(hwAddr, "00-0C-29-76-1D-D2") == 0)
    {
        printf("Packet being received by interface eth1\n");
    }
    else if(strcmp(hwAddr, "00-0C-29-76-1D-DC") == 0)
    {
        printf("Packet being received by interface eth2\n");
    }
    
     printf("   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", 
    eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    printf("   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
    printf("   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}

void print_ip_header(unsigned char* Buffer, int Size)
{
    //print_ethernet_header(Buffer , Size);

    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
    
    struct sockaddr_in source, dest;

    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;

    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    
    printf("\n");
    printf("IP Header\n");
    printf("   |-IP Version        : %d\n",(unsigned int)iph->version);
    printf("   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    printf("   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    printf("   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    printf("   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile , "   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile , "   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile , "   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    printf("   |-TTL      : %d\n",(unsigned int)iph->ttl);
    printf("   |-Protocol : %d\n",(unsigned int)iph->protocol);
    printf("   |-Checksum : %d\n",ntohs(iph->check));
    
    
    char ip[INET_ADDRSTRLEN] = {0};
    printf("   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    memset(ip, 0, INET_ADDRSTRLEN);
    printf("   |-Destination IP   : %s\n", inet_ntoa(dest.sin_addr));
    
}
                                 
    
    
int main()
{
    int sock_fd;

    sock_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if(sock_fd < 0)
    {
        printf("Cannot create socket: %s\n", strerror(errno));
        return -1;
    }

#if 0 /* binding to IPv4 address not worked  */
    struct sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(struct sockaddr_in));
    
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(0);

    /* bind the socket to localhost port 8888 */
    /*
    if (bind(sock_fd, (struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    */
#endif

#if 0
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));

    /* First Get the Interface Index */
    strncpy ((char*) ifr.ifr_name, "eth2", IFNAMSIZ);
    if ((ioctl(sock_fd, SIOCGIFINDEX, &ifr))== -1)
    {
        printf ("Error getting interface index!\n");
        exit(-1);
    }

    struct sockaddr_ll shwaddr;
    memset((void*)&shwaddr, 0, sizeof(struct sockaddr_ll));
    
    int ifindex;
    shwaddr.sll_family = PF_PACKET;   
    shwaddr.sll_ifindex = ifr.ifr_ifindex;
    shwaddr.sll_halen = ETH_ALEN;
    
    printf("ifindex : %u", ifr.ifr_ifindex);
    if (bind(sock_fd, (struct sockaddr *)&shwaddr, sizeof(struct sockaddr_ll)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
#endif
        
    printf("Starting\n");

    for( ; ; )
    {
#if 1
        fd_set rfds;

        FD_ZERO(&rfds);
        FD_SET(sock_fd, &rfds);

        int max_fd = sock_fd;

        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;

        int nfds;

        nfds = select(max_fd + 1, &rfds, NULL, NULL, &tv);
        
        //printf("\n select returned\n");

        if ((nfds < 0) && (errno!=EINTR)) 
        {
            printf("select error\n");
        }
        if(FD_ISSET(sock_fd, &rfds))
        {
            char buf[1024];
            int buflen = 1024;

            struct sockaddr_ll dhwaddr;
            socklen_t sendsize = sizeof(dhwaddr);
            memset(&dhwaddr, 0, sizeof(dhwaddr));

            int bytes = recvfrom(sock_fd, buf, buflen, 0, (struct sockaddr *)&dhwaddr, &sendsize);

            print_ethernet_header(buf, bytes);
            print_ip_header(buf, bytes);

            struct iphdr *iph = (struct iphdr*)(buf + sizeof(struct ethhdr));
            //printf("ethernet packet %u bytes received on socket\n", bytes);
        }
#else 
        printf("fdsfsdfsdfsdfd\n");
        char buf[1024];
        int buflen = 1024;

        struct sockaddr_ll dhwaddr;
        socklen_t sendsize = sizeof(dhwaddr);
        memset(&dhwaddr, 0, sizeof(dhwaddr));

        int bytes = recvfrom(sock_fd, buf, buflen, 0, NULL, NULL);
        //printf("ethernet packet %u bytes received on socket\n", bytes);

#endif
    }
}
