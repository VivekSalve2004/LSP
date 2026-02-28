#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock;
    
int iCnt = 0;

void * Increment(void *arg)
{
    pthread_mutex_lock(&lock);

        // Critical Section Start
        iCnt++;                         // shared resource
        // Critical Section End

        printf("%d\n",iCnt);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t t1 , t2;

    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1,NULL,Increment,NULL);
    pthread_create(&t2,NULL,Increment,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}