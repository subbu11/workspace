#include <stdio.h>
#include "common.h"

int global_1 = 10;
extern int global_2;
static int global_3;
extern global_4;

int main()
{
    printf("global_1 :: %u \n", global_1);
    printf("global_2 :: %u \n", global_2);
    printf("global_3 :: %u \n", global_3);
    printf("global_4 :: %u \n", global_4);

    func();
}
