/* This program swaps the nodes of linked list rather
 * than swapping the field from the nodes.*/

#include<stdio.h>
#include<stdlib.h>

/* A linked list node */
struct node
{
    int data;
    struct node *next;
    struct node *random;
};

/* Function to add a node at the begining of List */
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node =
        (struct node*) malloc(sizeof(struct node));

    /* put in the data */
    new_node->data = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);
    new_node->random = NULL;

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

void add_random(struct node* head, int nodeData, int randomData)
{
    struct node *curr;
    struct node *node;
    struct node *random;
    
    curr = head;
    while(curr != NULL)
    {
        if(curr->data == nodeData)
        {
            node = curr;
            break;
        }
        curr = curr->next;
    }

    curr = head;
    while(curr != NULL)
    {
        if(curr->data == randomData)
        {
            random = curr;
            break;
        }
        curr = curr->next;
    }

    if(node && random)
    {
        node->random = random;
    }
}

/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
    while(node != NULL)
    {
        printf("Node :: %d", node->data);
        
        if(node->next)
          printf("\tNext :: %d", node->next->data);
        else
          printf("\tNext :: NULL");
        
        if(node->random)
          printf("\tRandom :: %d\n", node->random->data);
        else
          printf("\tRandom :: NULL\n");
        
        node = node->next;
    }
}

void clone1(struct node* head)
{
    struct node *copyHead = NULL;
    struct node *curr = NULL;
    struct node *copyCurr = NULL;

    /* create nodes */
    /* point random of copy node to original random */ 
    /*
     * ---- DOES NOT WORK ----
    REASON :: When random of original node is pointed to copy node, 
              and random of original node is saved in random of copy node, 
              then it means, that the random of original node is to be fixed
              in the end (after all copy nodes is created), then at that time 
              we cannot fix the random of original node ONLY. So, we have to
              fix random of original node and copy node at the same time i.e. 
              same loop. But, this creates an error while fixing the random of 
              copy node as it is possible that node to which the random of copy 
              node is pointing is already fixed (i.e. the node to which the random
              of copy node was pointing is now pointing to original random node)
    */
                        
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = (struct node *)malloc(sizeof(struct node));
        copyNode->data    = curr->data;
        copyNode->next    = NULL;
        copyNode->random  = curr->random;
        curr->random      = copyNode;

        if(copyHead == NULL)
            copyHead  = copyNode;

        curr = curr->next;
    }

    /* Fix next of copy nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->random;
        if(curr->next)
          copyNode->next  = curr->next->random;

        curr = curr->next;
    }

#if 0 /* DON'T DO THIS :: this step makes the random of orignal node lost */
    /* Fix random of copy nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->random;
        if(copyNode->random)
          copyNode->random  = copyNode->random->random;

        curr = curr->next;
    }
#endif

    /* Fix random of copy nodes, at the same time fix random of original nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->random;
        if(copyNode->random)
        {
            struct node *tmp  = copyNode->random;
            copyNode->random  = copyNode->random->random;
            curr->random      = tmp;
        }

        curr = curr->next;
    }

    printf("Original :: \n");
    printList(head);
    printf("Copy :: \n");
    printList(copyHead);

}

void clone2(struct node* head)
{
    struct node *copyHead = NULL;
    struct node *curr = NULL;
    struct node *copyCurr = NULL;
 
    /*Method 2*/
    /* create nodes */
    /* point next of copy node to original random */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = (struct node *)malloc(sizeof(struct node));
        copyNode->data    = curr->data;
        copyNode->next    = curr->random;
        copyNode->random  = NULL;
        curr->random      = copyNode;

        if(copyHead == NULL)
            copyHead  = copyNode;

        curr = curr->next;
    }

    /* Fix random of copy nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->random;
        if(copyNode->next)
          copyNode->random  = copyNode->next->random;

        curr = curr->next;
    }

    /* Fix next of copy nodes, at the same time fix random of original nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->random;
        struct node *origRandom  = copyNode->next;

        if(curr->next)
            copyNode->next  = curr->next->random;
        else 
            copyNode->next  = NULL;

        curr->random =  origRandom;

        curr = curr->next;
    }


    printf("Original :: \n");
    printList(head);
    printf("Copy :: \n");
    printList(copyHead);

}

void clone3(struct node* head)
{
    struct node *copyHead = NULL;
    struct node *curr = NULL;
    struct node *copyCurr = NULL;

    /*Method 3*/
    /* create nodes */
    /* point next of copy node to original next */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = (struct node *)malloc(sizeof(struct node));
        copyNode->data    = curr->data;
        copyNode->next    = curr->next;
        copyNode->random  = NULL;
        curr->next        = copyNode;

        if(copyHead == NULL)
            copyHead  = copyNode;

        curr = copyNode->next;
    }

    /* Fix random of copy nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->next;
        if(curr->random)
            copyNode->random  = curr->random->next;

        curr = copyNode->next;
    }

    /* Fix next of copy nodes, at the same time fix next of original nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->next;
        struct node *origNext = copyNode->next;
        
        if(origNext)
            copyNode->next  = origNext->next;
        else 
            copyNode->next  = NULL;

        curr->next =  origNext;

        curr = curr->next;
    }


    printf("Original :: \n");
    printList(head);
    printf("Copy :: \n");
    printList(copyHead);
}

void clone4(struct node* head)
{
    struct node *copyHead = NULL;
    struct node *curr = NULL;
    struct node *copyCurr = NULL;

    /*Method 2*/
    /* create nodes */
    /* point random of copy node to original next */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = (struct node *)malloc(sizeof(struct node));
        copyNode->data    = curr->data;
        copyNode->random  = curr->next;
        copyNode->next    = NULL;
        
        curr->next        = copyNode;

        if(copyHead == NULL)
            copyHead  = copyNode;

        curr = copyNode->random;
    }

    /* Fix next of copy nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->next;
        if(copyNode->random)
            copyNode->next  = copyNode->random->next;

        curr = copyNode->random;
    }

    /* Fix random of copy nodes, at the same time fix next of original nodes */
    curr = head;
    while(curr != NULL)
    {
        struct node *copyNode = curr->next;
        struct node *origNext = copyNode->random;

        if(curr->random)
            copyNode->random  = curr->random->next;
        else 
            copyNode->random  = NULL;

        curr->next =  origNext;

        curr = curr->next;
    }


    printf("Original :: \n");
    printList(head);
    printf("Copy :: \n");
    printList(copyHead);
}

/* Druver program to test above function */
int main()
{
    struct node *start = NULL;

    /* The constructed linked list is:
     *  1->2->3->4->5->6->7 */
    push(&start, 7);
    push(&start, 6);
    push(&start, 5);
    push(&start, 4);
    push(&start, 3);
    push(&start, 2);
    push(&start, 1);

    add_random(start, 1, 7);
    add_random(start, 2, 1);
    add_random(start, 3, 5);
    add_random(start, 4, 6);
    add_random(start, 5, 2);
    add_random(start, 6, 4);
    add_random(start, 7, 3);

    printf("\n Method 1\n");
    clone1(start);
    printf("\n Method 2\n");
    clone2(start);
    printf("\n Method 3\n");
    clone3(start);
    printf("\n Method 4\n");
    clone4(start);

    return 0;
}

