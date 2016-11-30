#include <stdio.h>

int global_2 = 20;
extern int global_1;
static int global_3;

void func()
{
    printf("global_1 :: %u\n", global_1);
    printf("global_2 :: %u\n", global_2);
    printf("global_3 :: %u\n", global_3);
}
