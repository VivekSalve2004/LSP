#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() 
{
    int dirfd = open("/tmp", O_RDONLY | O_DIRECTORY);
    if (dirfd == -1) 
    { 
        perror("open dir"); return -1; 
    }

    int fd = openat(dirfd, "testfile.txt", O_CREAT | O_WRONLY, 0777);
    if (fd == -1) 
    { 
        perror("openat"); close(dirfd); return -1; 
    }

    write(fd, "Hello\n", 6);

    close(fd); 
    close(dirfd);

    printf("Created /tmp/testfile.txt\n");

    return 0;
}
