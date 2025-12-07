#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int fd = open("Marvellous.txt",O_RDONLY);
    printf("FD value : %d\n",fd);
    printf("value of errno is : %d\n",errno);

    return 0;
}