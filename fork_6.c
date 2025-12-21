#include<stdio.h>
#include<unistd.h>

int main()
{

    if(fork() == 0)
    {
        printf("Child Process Scheduled \n");
    }
    else
    {
        printf("Parent Process Scheduled \n");
    }

    
    
    return 0;
}