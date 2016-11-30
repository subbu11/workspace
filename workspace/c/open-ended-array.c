#include <stdio.h>
#include <stdlib.h>

struct test
{
      int a;
        char buf[];
};

int main(void) {

    struct test t;
    t.a = 10;
    void *mem = malloc(10);
    memcpy(t.buf, mem, 10);

    struct test *p1  = &t; 
    printf("a : %u\n", p1->a);


    char *pBuf = p1->buf;

    /* going back */
    struct test *p2 = (struct test *) ( (char *)pBuf - ( ((struct test *)0)->buf ) );

    printf("a : %u\n", p2->a);


    return 0;
}
