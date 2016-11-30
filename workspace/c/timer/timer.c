/*
 * program to demonstrate how to implement a timer and its timeout 
 */
#include <sys/select.h>
#include <stdio.h>

int main()
{
    struct timeval tv;
    int nfds;

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    nfds = select(1, NULL, NULL, NULL, &tv);

    if(nfds == 0)
    {
        printf("select timeout occured\n");
    }
}
