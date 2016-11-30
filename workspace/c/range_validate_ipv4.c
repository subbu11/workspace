#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    char s[20] = {0};
    char e[20] = {0};

    strcpy(s, argv[1]);
    strcpy(e, argv[2]);

    uint32_t sIp = 0;
    uint32_t eIp = 0;

    int r = inet_pton(AF_INET, s, &sIp);
    if(r <= 0)
    {
        printf("wrong START\n");
        exit(-1);
    }

    r = 0;
    r = inet_pton(AF_INET, e, &eIp);
    if(r <= 0)
    {
        printf("wrong END\n");
        exit(-1);
    }

    printf("S :: %u E :: %u\n", sIp, eIp);
    printf("S :: %08X E :: %08X\n", sIp, eIp);
    if(ntohl(sIp) > ntohl(eIp))
    {
        printf("WRONG\n");
    }
    else 
    {
        printf("OK\n");
    }
}
