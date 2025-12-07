#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid = 0;

    pid = fork();

    printf("%d\n",pid);

    return 0;
}