#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

int main()
{
    int id = 0;
    char *ptr = NULL;

    key_t key;

    key = ftok(".",'s');        // "."  current directory

    id = shmget(key,1024,0666 | IPC_CREAT);

    if(id == -1)
    {
        printf("Failed to allocate shared memory\n");
        return -1;
    }

    ptr = shmat(id,NULL,0);

    if(ptr == (char *)-1)
    {
        printf("unable to attach memory\n");
        return-1;
    }

    *ptr = 'L';
    ptr++;

    *ptr = 'S';
    ptr++;

    *ptr = 'P';
    ptr++;

    *ptr = '\0';

    shmdt(ptr);

    return 0;
}