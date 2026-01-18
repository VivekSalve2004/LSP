#include<stdio.h>
#include<pthread.h>

void *Demo(void *p)
{
    printf("Inside thread\n");
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    pthread_t TID;
    int iRet = 0;

    printf("Main thread started \n");

    // Creation of thread + Exection of thread
    iRet = pthread_create(&TID ,     // Thread ID
                         NULL ,     // Thread Attributes
                         Demo ,     // Thread callback function
                         NULL );    // parameters for callback function
             
    if(iRet == 0)
    {
        printf("Thread gets created successfully with TID %lu \n",(unsigned long)TID);
        
    }                     

    // wait
    pthread_join(TID , NULL) ;

    pthread_exit(NULL);

    printf("End of main thread \n");

    return 0;
}