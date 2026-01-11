// without using write system call data gets written into a file 
// the stdout is closed (printf() is closed)
// and a file (sample.txt) gets opened with its fd occupying space of stdout fd entry in ufdt (first empty entry in ufdt gets occupied by this file descriptor)
// any printf() call will print (or write) the output to opened file with its fd instead of stdout(console)

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    printf("Before closing stdout \n");

    close(1);

    printf("After stdout is closed \n");

    int fd = open("sample.txt",O_CREAT | O_WRONLY,0777);

    printf("Text gets written into sample.txt\n");

    close(fd);

    return 0;
}