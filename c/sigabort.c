#include <stdio.h>
#include <stdint.h>

struct data
{
    uint32_t a;
    uint32_t b;
};

int main()
{
    struct data d[2] = {{10, 20}};

    struct data* pData[2];
    pData[0] = &d[0];
    pData[1] = &d[1];

#define GET_DATA(__index)       (pData[__index])
    
    struct data *p = GET_DATA(2000);
    if(p)
    {
        printf("NOT NULL\n");
        printf("data :: a = %u, b = %u\n", p->a, p->b);
    }
    else
    {
        printf("NULL\n");
    }
}
