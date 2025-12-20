#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    int fd = 0;
    fd = open("./test/LSPl.txt" , O_RDONLY);                        // Issue

    if(fd == -1)
    {
        printf("Unable to open file %s \n" , strerror(errno));
        return -1;
    }

    printf("File opened with fd : %d\n",fd);

    close(fd);

    return 0;
}