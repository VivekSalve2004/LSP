#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("PID of Current process is : %d\n",getpid());
    printf("PID of Parent process is : %d\n",getppid());

    return 0;
}