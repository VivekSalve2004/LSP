#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define SHMSZ 30

int main()
{
    char c;
    int shmid;
    char *shm, *s;

    printf("Demo of IPC using Shared Memory\n");

    key_t key = ftok(".",'a'); // Generate key

    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666); // Create the segment

    shm = shmat(shmid, NULL, 0); // Attach segment to our data space

    s = shm; // base address of shared memory

    for (c = 'a'; c <= 'z'; c++)
    {
        *s = c;
        s++;
    }
    printf("Data is written in Shared Memory\n");
    *s = '\0';
    // Wait until other process changes the first character of our memory to '*'
    // indicating that it has read what we put there.
    while (*shm != '*')
    {
        sleep(1);
    }

    printf("Data is Successfully fetched by client\n");
    printf("Terminating server\n");

    exit(0);

}