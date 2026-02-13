#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    printf("PID of running process is : %d\n",getpid());
    printf("PID of parent process is : %d\n",getppid());

    return 0;
}