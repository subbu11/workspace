#include <stdio.h>
#include <string.h>

void toggle(char *str, int len)
{
    int i = 0;
    
    for(i = 0; i < len; i++)
    {
        if(str[i] == '1')
            str[i] = '0';
        else 
            str[i] = '1';
    }
}

int count(char *str, int len)
{
    int i = 0;
    int count = 0;

    printf("Count for %s upto len %u\n", str, len);
    for(i = 0; i < len; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");

    
    for(i = 0; i < len; i++)
    {
        if(str[i] == '1')
            ++count;
    }

    return count;
}

int rev_count(char *str, int len)
{
    //printf("str : %s\n", str);
    //printf("len : %u\n", len);
    int i = 0;
    int count = 0;
    printf("Rev-Count for %s upto len %u\n", str, len);

    for(i = 0; i < len; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
    
    for(i = 0; i < len; i++)
    {
        if(str[i] == '0')
            ++count;
    }
    return count;
}

int max1s(char *str, int len)
{
    int start = 0;
    int end = 0;

    for(end = 0; end < len; end++)
    {
        for(start = 0; start < end; start++)
        {
            printf("start = %u end = %u\n", start, end);
            //printf("%c\n", str[start]);
            int toggleCount = rev_count(&str[start], end - start + 1);
            printf("toggle count : %u \n", toggleCount);
            int remCount       = count(&str[end + 1], len - end - 1);
            printf("remcount : %u \n", remCount);
            printf("-------\n");
        }
    }
}

int main()
{
    char str1[] = "1010";
    char str2[] = "10111";

    printf("%u\n", max1s(str1, strlen(str1)));
    //printf("%u\n", max1s(str2, strlen(str2)));
}
