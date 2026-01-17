#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

int main()
{
    int id = 0;
    char *ptr = NULL;

    key_t key;

    key = ftok(".",'s');

    id = shmget(key,1024,0666);

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

    printf("%s \n" , ptr);

    shmdt(ptr);

    return 0;
}