/*
 * Listens on Multicast IP and PORT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "multicast.h"

int main()
{
    struct sockaddr_in localAddr;
    int sock_fd;
    int ret;
    char buffer[1024];

    /*fill local address*/
    memset(&localAddr, 0, sizeof(struct sockaddr_in));
    localAddr.sin_family      = AF_INET;
    localAddr.sin_addr.s_addr = ntohl(INADDR_ANY);
    localAddr.sin_port        = htons(M_CAST_PORT);

    /* create socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd  <= 0)
    {
        printf("socket() : cannot create socket %u\n", sock_fd);
        exit(-1);
    }

    /* make the socket non-blocking */
    int optval = 1;
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        printf("setsockopt : cannot make socket non-blocking\n");
        exit(-1);
    }

    /* bind socket to localAddr */
    ret = bind(sock_fd, (struct sockaddr *)&localAddr, sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        printf("bind() : cannot bind\n");
        exit(-1);
    }

    /* Add to multicast group */
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(M_CAST_IP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("setsockopt : cannot add to multicast group");
        exit(1);
    }
    
    /* keep listening for messages */
    while(1)
    {
        struct sockaddr_in remoteAddr;
        int remoteAddrLen = 0;
        int nbytes = recvfrom(sock_fd, buffer, 1024, 0,
            (struct sockaddr *)&remoteAddr, &remoteAddrLen);
        if(nbytes < 0)
        {
            printf("recvfrom() : receive failed %u\n", nbytes);
        }
        printf("Message Received : %s\n", buffer);
    }
}
