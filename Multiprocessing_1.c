#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    pid_t pid1 = 0;
    pid_t pid2 = 0;

    pid1 = fork();

    if(pid1 == 0)
    {
        execl("./Capital" , "" , NULL);
    }
    else
    {
        
    }

    pid2 = fork();

    if(pid2 == 0)
    {
        execl("./Small" , "" , NULL);
    }
    else
    {
        
    }

    printf("End of main process \n");

    return 0;
}