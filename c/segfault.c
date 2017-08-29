#include <stdio.h>
#include <pthread.h>
#include <execinfo.h>

typedef struct SessionS
{
    int i;
    pthread_mutex_t mutex;
} SessionT;

typedef struct BearerS
{
   SessionT* pSession;
} BearerT;

int main()
{
    void *buf[40960] = {0};

    printf("starting\n");
    SessionT session;
    session.i = 10;
    pthread_mutex_init(&session.mutex, NULL);

    BearerT bearer;
    bearer.pSession = &session;

    SessionT* pSession1 = bearer.pSession;
    pthread_mutex_lock(&(pSession1->mutex));

    BearerT *pBearer = NULL; 

    if(pBearer == NULL || pBearer->pSession)
    {
        printf("ERRRROOOOOOOOORRRRRRRRRRRRRRRR\n");
        return;
    }

    backtrace(buf, 40960);
    SessionT* pSession2 = NULL;
    printf("mutex : %u\n", pSession2->mutex);
    pthread_mutex_lock(&(pSession2->mutex));

    backtrace(buf, 40960);

    printf("exiting\n");
}
