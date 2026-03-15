#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char Arr[10];

    fd = open("test.c",O_RDONLY);

    read(fd,Arr,5);

    printf("%s\n",Arr);

    close(fd);

    return 0;
}