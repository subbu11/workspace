/* 
 * Sends UDP messages to servers listening on multicast IP
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "multicast.h"

int main()
{
    struct sockaddr_in remoteAddr;
    int sock_fd;
    char *message = "Hey There !";

    /* Fill source Address */
    memset(&remoteAddr, 0, sizeof(struct sockaddr_in));
    remoteAddr.sin_family       = AF_INET;
    remoteAddr.sin_addr.s_addr  = inet_addr(M_CAST_IP);
    remoteAddr.sin_port         = ntohs(M_CAST_PORT);

    /* create socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd <= 0)
    {
        printf("socket() : cannot be created %u\n", sock_fd);
        exit(-1);
    }

    /* Send message */
    while(1)
    {
        if(sendto(sock_fd, message, strlen(message), 0, 
                    (struct sockaddr *)&remoteAddr, 
                    sizeof(remoteAddr)) < 0)
        {
            printf("sendto() : failed to send message to server IP: %u.%u.%u.%u Port:%u \n", remoteAddr.sin_addr.s_addr & 0xFF ,
                    (remoteAddr.sin_addr.s_addr & 0xFF00) >> 8,
                    (remoteAddr.sin_addr.s_addr & 0xFF0000) >> 16,
                    (remoteAddr.sin_addr.s_addr & 0xFF000000) >> 24,
                    ntohs(remoteAddr.sin_port));
            //exit(-1);
        }
        printf("Message sent : %s\n", message);
        sleep(1);
    }
}
