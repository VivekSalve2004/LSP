#include<stdio.h>
#include<pthread.h>

void *Demo(void *p)
{
    printf("Inside Demo thread\n");
    return NULL;
}

void *Hello(void *p)
{
    printf("Inside Hello thread\n");
    return NULL;
}

int main()
{
    pthread_t TID1,TID2;
    int iRet = 0;

    printf("Main thread started \n");

    // Creation of thread + Exection of thread
    iRet = pthread_create(&TID1 ,     // Thread ID
                         NULL ,     // Thread Attributes
                         Demo ,     // Thread callback function
                         NULL );    // parameters for callback function
             
    if(iRet == 0)
    {
        printf("Thread gets created successfully with TID %lu \n",(unsigned long)TID1);
        
    }  
    
    iRet = pthread_create(&TID2 ,     // Thread ID
                         NULL ,     // Thread Attributes
                         Hello ,     // Thread callback function
                         NULL );    // parameters for callback function
             
    if(iRet == 0)
    {
        printf("Thread gets created successfully with TID %lu \n",(unsigned long)TID2);
        
    }  

    // wait
    pthread_join(TID1 , NULL) ;
    pthread_join(TID2 , NULL) ;

    printf("End of main thread \n");

    return 0;
}