#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_rwlock_t rwlock_id;
int var_global  = 4;

time_t now, later;
double seconds;

void * Read_Lock_Thread()
{
    int ret, i=0;
    time(&now);
    while(i < 2)
    {
        time(&later);
        seconds = difftime(later, now);
        printf("READ THREAD : %d :trying to acquire lock\n", 
        i);

        ret = pthread_rwlock_rdlock(&rwlock_id);
        if(ret != 0)
            perror("error in read lock taking");

        time(&later);
        seconds = difftime(later, now);
        printf("READ THREAD : %d :value of global variable is %d\n", 
                i, var_global);

        sleep(10);

        ret = pthread_rwlock_unlock(&rwlock_id);
        if(ret != 0)
            perror("read un-lock");

        time(&later);
        seconds = difftime(later, now);
        printf("READ THREAD : %d :released lock, sleeping for 1 sec\n",
                i); 

        i++; 

        /* after releasing lock, let the writer thread acquire lock*/
        sleep(1);

        time(&later);
        seconds = difftime(later, now);
        printf("READ THREAD : %d :woke up\n",
                i); 

    }
}

void * Write_Lock_Thread()
{
    int ret;
    time(&now);

    time(&later);
    seconds = difftime(later, now);
    printf("WRITE THREAD : trying to acquire lock\n");

    ret = pthread_rwlock_wrlock(&rwlock_id);
    if(ret != 0)
        perror("error in write lock taking");

    printf(" WRITE THREAD : value of global variable is %d\n", var_global);
    var_global = 5;
    printf(" WRITE THREAD : value of global variable changed is %d\n", var_global);
    
    ret = pthread_rwlock_unlock(&rwlock_id);
    if(ret != 0)
        perror("Write un-lock");

    time(&later);
    seconds = difftime(later, now);
    printf("WRITE THREAD : releasing lock\n");
}

int main()
{
    int ret;
    pthread_t thread_id[2];
    
    time(&now);
    /* initializing read write lock */
    ret = pthread_rwlock_init(&rwlock_id, NULL);
    if(ret != 0)
        perror("RWlock initialize ");

    /*  Creates thread which only read the value */
    ret = pthread_create(&thread_id[0], NULL, Read_Lock_Thread, NULL);
    if(ret != 0)
        perror("Read lock thread ");
    
    /* Creates thread which only Write the value */
    ret = pthread_create(&thread_id[1], NULL, Write_Lock_Thread, NULL);
    if(ret != 0)
        perror("Write lock thread ");
    
    /* thread_id[0] has acquired lock, still Main thread can access value*/
    time(&later);
    seconds = difftime(later, now);
    printf("MAIN THREAD : sleeping for 2 seconds\n");
    
    sleep(2);

    time(&later);
    seconds = difftime(later, now);
    printf("MAIN THREAD : woke up, trying to acquire lock\n");
    
    /* Main Thread acquired lock */
    ret = pthread_rwlock_rdlock(&rwlock_id);
    if(ret != 0)
        perror("error in read lock taking");
    
    printf(" MAIN THREAD : value of global variable is %d\n", var_global);

    ret = pthread_rwlock_unlock(&rwlock_id);
    if(ret != 0)
        perror("Write un-lock");

    time(&later);
    seconds = difftime(later, now);
    printf("MAIN THREAD : release lock\n");
 
    /* Main thread released lock */

    pthread_join(thread_id[0],NULL);  
    pthread_join(thread_id[1],NULL);  
}
