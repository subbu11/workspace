#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <errno.h>
int main()
{
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
    {
        printf("sokcet functin failed : \n");
        exit (-1);
    }
    
    char packet[512];

    struct sockaddr_in remote; // remote address
    /*
    struct iphdr *ip = (struct iphdr *) packet; // ip header
    struct tcphdr *tcp = (struct tcphdr *) packet + sizeof(struct iphdr); // tcp header
    */

    
    struct tcphdr *tcp = (struct tcphdr *) packet; // tcp header
    
    remote.sin_family = AF_INET; // family
    remote.sin_addr.s_addr = inet_addr("192.168.0.57"); // destination ip
    remote.sin_port = htons(3868); // destination port

    memset(packet, 0, 512); // set packet to 0
    
    /*
    if((setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&enable, sizeof(enable))) < 0) 
    { // set socket options
        printf("\nError: Can't set socket options!\n\n");
        return -1; 
    }
    */

    /*
    ip->ihl = 5; // header length
    ip->version = 4; // ip version
    ip->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    ip->id = htons(2500); // id sequence number (value doesnt matter)
    ip->saddr = inet_ntoa(atoi(argv[3])); // source ip
    ip->daddr = inet_ntoa(atoi(argv[1])); // destination ip
    ip->ttl = htons(atoi(argv[5])); // ttl
    ip->protocol = 6; // protocal number
    ip->check = 0; // ip checksum
    ip->tos = 0; // type of service
    ip->frag_off = 0; // fragment offset
    */
    
    tcp->source = htons(3868); // source port
    tcp->dest = htons(5868); // destination port
    tcp->seq = htons(random()); // inital sequence number
    tcp->ack_seq = htons(0); // acknowledgement number
    tcp->ack = 0; // acknowledgement flag
    tcp->syn = 1; // synchronize flag
    tcp->rst = 0; // reset flag
    tcp->psh = 0; // push flag
    tcp->fin = 0; // finish flag
    tcp->urg = 0; // urgent flag
    tcp->check = 0; // tcp checksum
    tcp->doff = 5; // data offset
    //tcp->window = htons(1200); // window size

    printf("\nSimple Packet Crafter using raw sockets\n");
    printf("\nPacket Data: \n");

    int i = 0;
    for(i=0; i < 512; i++)
    {
        if(i % 8 == 0)
          printf("\n");
        printf("%02X ", packet[i]);
    }
    printf("\n");
    //printf("\nDestination IP: %s", argv[1]);
    //printf("\nDestination Port: %s", argv[2]);
    //printf("\nSource IP: %s", argv[3]);
    //printf("\nSource Port: %s", argv[4]);
    //printf("\nTTL: %s", argv[5]);
    //printf("\nWindow Size: %s\n", argv[6]);

    //printf("\nSending packet to %s...\n", argv[1]);
    int err; 
    if((err = sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&remote, sizeof(struct sockaddr))) < 0) 
    { // send packet 
        int saved_err = errno;
        printf("Error: Can't send packet : %d %d !\n\n", err, saved_err);
        printf("Error: Can't send packet : %s!\n\n", strerror(saved_err));
        return -1; 
    }

    printf("\nPacket sent ! Goodbye!\n\n"); 
}
