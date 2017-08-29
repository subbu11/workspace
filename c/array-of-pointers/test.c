#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int val[1000000];
} Bucket;

typedef struct
{
    int size;
    Bucket** bucketArr;
} Table; 

int main()
{
    Table *tbl = malloc(sizeof(Table));
    tbl->bucketArr = malloc(sizeof(Bucket*) * 10);

    int i = 0;
    for(i = 0; i < 10; i++)
        tbl->bucketArr[i] = NULL;

    for(i = 0; i < 10; i++)
        printf("bucketArr[%d] = %p\n", i, &tbl->bucketArr[i]);

    printf("\nMemory allocating\n");
    for(i = 0; i < 10; i++)
    {
        tbl->bucketArr[i] = malloc(sizeof(Bucket));
        printf("&bucketArr[%d] = %p ", i, &tbl->bucketArr[i]);
        printf("bucketArr[%d] = %p\n", i, tbl->bucketArr[i]);
    }

    printf("\nMemory freeing\n");
    for(i = 0; i < 10; i++)
    {
        free(tbl->bucketArr[i]);
        printf("&bucketArr[%d] = %p ", i, &tbl->bucketArr[i]);
        printf("bucketArr[%d] = %p\n", i, tbl->bucketArr[i]);
    }

    printf("\n");

    Table *tbl2 = malloc(sizeof(Table));
    tbl2->bucketArr = malloc(sizeof(Bucket) * 10);

    for(i = 0; i < 10; i++)
        tbl2->bucketArr[i] = NULL;

    for(i = 0; i < 10; i++)
    {
        printf("bucketArr[%d] = %p\n", i, &tbl2->bucketArr[i]);
    }

    sleep(60);
    printf("\nMemory allocating\n");
    for(i = 0; i < 10; i++)
    {
        tbl2->bucketArr[i] = malloc(sizeof(Bucket));
        printf("&bucketArr[%d] = %p ", i, &tbl2->bucketArr[i]);
        printf("bucketArr[%d] = %p\n", i, tbl2->bucketArr[i]);
    }

    sleep(60);


    printf("\nMemory freeing\n");
    for(i = 0; i < 10; i++)
    {
        free(tbl2->bucketArr[i]);
        printf("&bucketArr[%d] = %p ", i, &tbl2->bucketArr[i]);
        printf("bucketArr[%d] = %p\n", i, tbl2->bucketArr[i]);
    }

    getchar();
}
