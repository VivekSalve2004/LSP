#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int pipefd[2] = {0,0};
    int iRet = 0;
    char Arr[100] = {'\0'};

    pipe(pipefd);               // anonymous pipe

    iRet = fork();

    if(iRet == 0)           // child
    {
        close(pipefd[0]);
        write(pipefd[1],"Jay Ganesh",10);
        exit(0);
    }
    else                    // parent
    {
        close(pipefd[1]);
        read(pipefd[0] , Arr , 10);
        printf("Data from file is : %s\n",Arr);
        
    }

    return 0;
}