#include <stdio.h>
#include <string.h>
#include "tree.h"

/**
 * RB_INSERT_COLOR ---> key is found in map, but pointer is not found.
 * RB_REMOVE_COLOR ---> key is found in map, but pointer is not found.
 *
 **/

typedef struct InfoS
{
   int key;
   RB_ENTRY(InfoS)    node;                  /**< RB Tree Data Structure Node        */
   struct InfoS *next;
} InfoT;


static inline int
compareNode(InfoT* a, InfoT* b)
{
   if(a->key > b->key)
    return 1;
   if(a->key < b->key)
    return -1;
   return 0;
}

RB_HEAD(InfoMap, InfoS) map;
RB_GENERATE(InfoMap, InfoS, node, compareNode);

int main()
{
    InfoT i1 = {0};
    i1.key = 10;
    printf("node == %08X\n", &i1);

    printf("INSERTING i1=%08X", &i1);
    InfoT* check = RB_INSERT(InfoMap, &map, &i1);

    if(check == NULL)
    {
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");
    
    InfoT i2 = {0};
    i2.key = 10;
    printf("node == %08X\n", &i2);

    printf("INSERTING i2=%08X", &i2);
    check = RB_INSERT(InfoMap, &map, &i2);

    if(check == NULL)
    {
        printf("success\n");
    }
    else
    {
        printf("check == %08X\n", check);
        printf("failed\n");
    }
    printf("\n\n\n\n");
    
    printf("REMOVING i1=%08X", &i1);
    check = RB_REMOVE(InfoMap, &map, &i1);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");

    check = RB_FIND(InfoMap, &map, &i1);
    if(check)
    {
        printf("FOUND check=%08X\n", check);
    }
    else
    {
        printf("NOT FOUND %08X\n", check);
    }

    check = RB_FIND(InfoMap, &map, &i2);
    if(check)
    {
        printf("FOUND check=%08X\n", check);
    }
    else
    {
        printf("NOT FOUND %08X\n", check);
    }

    printf("REMOVING i1=%08X", &i1);
    check = NULL;
    check = RB_REMOVE(InfoMap, &map, &i1);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");

    printf("REMOVING i2=%08X", &i2);
    check = NULL;
    check = RB_REMOVE(InfoMap, &map, &i2);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");
}
