#include <stdio.h>

int main()
{

    char mybuf[] = "Brocade";
    char yourbuf[] = "Rules";
    char *const ptr = mybuf;
    *ptr = 'a';
    ptr = yourbuf;
    return 0;
}
