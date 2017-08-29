#include <stdio.h>
#include <unistd.h>

typedef struct BucketS 
{
    void* key;
    void* data;
    struct BucketS* next;
} Bucket;

int main()
{
    Bucket* b = malloc(sizeof(Bucket));

    printf("starting\n");
    sleep(15);

    printf("allocating\n");
    b->key      = malloc(sizeof(int));
    b->data     = malloc(500000000);
    
    sleep(45);
    printf("freeing\n");


    free(b->key);
    free(b);

    sleep(25);
    printf("freeing data\n");

    free(b->data);

    sleep(25);
}
