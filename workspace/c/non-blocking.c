/*
 * Make a socket non-blocking 
 *
 */
#include <stdio.h>
#include <sys/socket.h> /* socket() */
#include <fcntl.h> /* fcntl() */
#include <string.h> /* strerror() */
#include <errno.h> /* errno() */

int main()
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    int flags; 

    /* Get socket flags */ 
    if ((flags = fcntl(sock_fd, F_GETFL, 0)) < 0) 
    { 
        /* Handle error */ 
        printf("Error in getting socket flags : %s\n", strerror(errno)); 
    } 
    
    /* Set socket flags */ 
    flags |= O_NONBLOCK;
    if (fcntl(sock_fd, F_SETFL, flags) < 0) 
    { 
        /* Handle error */ 
        printf("Error in setting socket flags : %s\n", strerror(errno)); 
    }
    flags = 0;

    /* check socket flags */ 
    if ((flags = fcntl(sock_fd, F_GETFL, 0)) < 0) 
    { 
        /* Handle error */ 
        printf("Error in getting socket flags : %s\n", strerror(errno)); 
    }

    if(flags & O_NONBLOCK)
    {
        printf("Socket in NON-BLOCKING\n");
    }
    else
    {
        printf("Socket in BLOCKING\n");
    }
}
