#include<stdio.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<string.h>

#define MAXTEXT 512

struct MarvellousMessage
{
    long int msg_type;
    char data[MAXTEXT];
};

int main()
{
    key_t key;
    int id = 0;
    int iRet = 0;
    struct MarvellousMessage mobj;

    key = ftok(".",'a');

    id = msgget(key,0666);

    if(id == -1)
    {
        printf("Unable to allocate message queue\n");
        return -1;
    }

    iRet = msgrcv(id , (void *) &mobj , MAXTEXT , 11 , IPC_NOWAIT);

    if(iRet > 0)
    {
        printf("Data received from message queue is : %s\n",mobj.data);
    }



    return 0;
}