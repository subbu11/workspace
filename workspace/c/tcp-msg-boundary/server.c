/*
 * TCP client to send messages to TCP server
 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> // IPPROTO_TCP
#include <errno.h>

#include "api.h"

int main()
{
    /* create socket */
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sd < 0)
    {
        printf("Socket creation failed\n");
        return -1;
    }
    else 
    {
        printf("socket created\n");
    }
    
    /* bind the socket to a address*/
    struct sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(struct sockaddr_in));
    
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = inet_addr("192.168.0.51");
    localAddr.sin_port = htons(SERVER_PORT);
    
    int rc;
    rc = bind(sd, (struct sockaddr *)&localAddr, sizeof(localAddr));
    if(rc < 0)
    {
        printf("Bind failed\n");
    }
    else 
    {
        printf("bind succcess\n");
    }

    /* listen */
    rc = listen(sd, 10);
    if(rc < 0)
    {
        printf("Listen failed\n");
    }
    else 
    {
        printf("listen succcess\n");
    }

    /* accept TCP connection */
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);

    int client_sd = accept(sd, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sd < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    while(1)
    {
        //Receive a message from client
        char client_message[20000];
        char *ptr = client_message;

        int expLen = sizeof(MsgT);
        int bytesLeft =  expLen;

        while(bytesLeft > 0)
        {
            int bytesRead;
            if((bytesRead = read(client_sd , client_message, bytesLeft)) > 0 )
            {
                printf("Received %u bytes\n", bytesRead); 

                bytesLeft = bytesLeft - bytesRead;
                ptr = ptr + bytesRead;

                printf("\n");
            }
            else if(bytesRead == 0)
            {
                /*EOF*/
                puts("Client disconnected\n");
                fflush(stdout);
                return;
            }
            else if(bytesRead < 0)
            {
                if(errno == EINTR)
                {
                    printf("Read interrupted\n");
                }
                else
                {
                    printf("read failed\n");
                    return -1;
                }
            }
        }

        /* using Message length to verify the message */
        MsgT *m = client_message;
        printf("len : %u\n", m->len);
        
        printf("u64 : 0x%016llX\n", m->u64);
        printf("u32 : 0x%08X, 0x%08X\n", m->u32[0], m->u32[1]);
        printf("u8 : 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X\n", 
                m->u8[0], m->u8[1], m->u8[2], m->u8[3],
                m->u8[4], m->u8[5], m->u8[6], m->u8[7]);

        int i;
        for(i = 0; i < m->len; i++)
        {
            //printf("%c ", m->data[i]);
        }
        printf("\n");
    }
}
