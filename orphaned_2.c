#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t pid = 0;

    pid = fork();

    if(pid == 0)        // Child process
    {
        printf("Child process is running\n");
        printf("PID of child is : %d & PPID of child is : %d\n",getpid(),getppid());
        sleep(20);      // Child process goes to SLEEP State
        printf("PID of child is : %d & PPID of child is : %d\n",getpid(),getppid());
        exit(0);
    }
    else                // Parent process
    {
        printf("Parent process is running\n");
        printf("PID of Parent is : %d & PPID of Parent is : %d\n",getpid(),getppid());
        exit(1);
    }
    return 0;
}