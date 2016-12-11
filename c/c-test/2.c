#include <stdio.h>

int main()
{
    int i=5;
    
    scanf("%c", &i);
    printf("%d\n", i);

    scanf("%s", &i);
    printf("%d\n", i);

    for(;scanf("%s", &i); printf("%d\n", i));

    return 0;
}
