#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t pid = 0;
    
    pid = fork();

    if(pid == 0)
    {
        sleep(10);
        printf("Child process is running\n");
    }
    else
    {
        printf("Parent process is running\n");
    }

    return 0;
}