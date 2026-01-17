#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<stdlib.h>
#define SHMSZ 30
int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    printf("Demo of IPC using Shared Memory\n");
    printf("Client is running\n");

    key = ftok(".",'a');

    shmid = shmget(key, SHMSZ, 0666);

    shm = shmat(shmid, NULL, 0);

    printf("Data received from Server\n");
    for (s = shm; *s != '\0'; s++)// Now read what the server put in the memory.
    {
        printf("%c",*s);
    }

    *shm = '*'; // change the first character of the segment to '*', indicating we have
    // read the segment.

    printf("\nTerminating the Client\n");

    exit(0);
}

////////////////////////////////////////////////////////////////////////

/* 

OUTPUT -
Demo of IPC using Shared Memory
Client is running
Data received from Server
abcdefghijklmnopqrstuvwxyz
Terminating the Client

*/