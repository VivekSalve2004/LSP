#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    int pid = 0;

    printf("Enter pid of process : \n");
    scanf("%d",&pid);

    kill(pid , SIGUSR1);

    return 0;
}