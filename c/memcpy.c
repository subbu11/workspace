#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct 
{
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint8_t  buf[];
} data;

int main()
{
    uint8_t src[100];
    uint8_t dst[2000];
    uint32_t size = 3000;

    //memcpy(dst, src, size);
    
    uint8_t* pSrc = src;
    uint8_t* pDst = src + 8;

    memcpy(pDst, pSrc, 40);
    memcpy(pSrc, pDst, 40);

    printf("sizeof:: %u\n", sizeof(data));
    printf("success\n");
}
