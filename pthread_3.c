#include<stdio.h>
#include<pthread.h>

void *Demo(void *p)
{
    printf("Inside thread\n");
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
        printf("Thread gets created successfully\n");
        
    }                     

    // wait
    

    printf("End of main thread \n");

    return 0;
}