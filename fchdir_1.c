#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>

int main()
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("Original CWD: %s\n", cwd);

    int fd = open("/tmp", O_RDONLY | O_DIRECTORY);
    if(fd == -1) 
    {
        perror("open");
        return -1;
    }

    if(fchdir(fd) == -1) 
    {
        perror("fchdir");
        close(fd);
        return -1;
    }

    getcwd(cwd, sizeof(cwd));
    printf("New CWD: %s\n", cwd);

    close(fd);

    return 0;
}