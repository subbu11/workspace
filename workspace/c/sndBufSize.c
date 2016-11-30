#include <sys/socket.h>
#include <stdio.h>

int main()
{
    int sockfd;
    
    /* create UDP socket */
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("sockfd : error\n");
        exit(-1);
    }

    /* find sendBufferSize */
    int sndBufSize;
    socklen_t s = sizeof(sndBufSize);

    if((s = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndBufSize, &s)) < 0)
    {
        printf("getsockopt : error\n");
        exit(-1);
    }

    printf("SendBufferSize : %u\n", sndBufSize);

    /* set new sendBufferSize */
    sndBufSize = 100000;
    s = sizeof(sndBufSize);

    if((s = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndBufSize, s)) < 0)
    {
        printf("setsockopt : error\n");
        exit(-1);
    }
    
    /* get new sendBufferSize */
    sndBufSize = 0;
    s = sizeof(sndBufSize);
    if((s = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndBufSize, &s)) < 0)
    {
        printf("getsockopt : error\n");
        exit(-1);
    }
    printf("SendBufferSize : %u\n", sndBufSize); 
    /* 
       SO_SNDBUF
       Sets or gets the maximum socket send buffer in bytes.  The  ker-
       nel doubles this value (to allow space for bookkeeping overhead)
       when it is set using setsockopt(), and  this  doubled  value  is
       returned  by  getsockopt().   The  default  value  is set by the
       wmem_default sysctl and the maximum allowed value is set by  the
       wmem_max sysctl.  The minimum (doubled) value for this option is
       2048. 
    */
}
