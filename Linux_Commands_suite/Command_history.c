// gcc Command_history.c -o history -lreadline
// ./history

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define SIZE 1024

int main()
{
    int fd = 0;           
    int iRet = 0;
    char buffer[SIZE];   
    char path[1024];

    sprintf(path, "%s/.bash_history", getenv("HOME"));

    fd = open(path, O_RDONLY);

    if (fd == -1) 
    {
        perror("Error : Shell History is inaccessible \n");
        return -1;
    }

    printf("Reading history using system calls:\n");

    while ((iRet = read(fd, buffer, SIZE)) != 0) 
    {
        write(1, buffer, iRet); 
    }

    close(fd);

    return 0;
}