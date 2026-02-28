#include<stdio.h>
#include<pthread.h>

int iCnt = 0;

void * Increment(void *arg)
{
    // Critical Section Start
    iCnt++;         // shared resource
    // Critical Section End

    printf("%d\n",iCnt);

    return NULL;
}

int main()
{
    pthread_t t1 , t2;

    pthread_create(&t1,NULL,Increment,NULL);
    pthread_create(&t2,NULL,Increment,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}