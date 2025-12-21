#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    int fd1 = 0 , fd2 = 0;

    fd1 = open("./LSP.txt" , O_RDWR);

    printf("fd1 : %d\n",fd1);

    fd2 = dup2(fd1 , 11);

    printf("fd2 : %d\n",fd2);

    return 0;
}