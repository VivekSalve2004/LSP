#define _GNU_SOURCE  /* Required for dup3 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() 
{
    int iRet = 0;
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
    {
        perror("Failed to open file");
        return -1;
    }

    // Atomically duplicate fd onto STDOUT_FILENO (fd 1)
    // O_CLOEXEC ensures the file closes if we execute another program.
    iRet = dup3(fd, STDOUT_FILENO, O_CLOEXEC);
    if (iRet == -1) 
    {
        perror("dup3 failed");
        close(fd);
        return -1;
    }

    printf("%d\n",iRet);

    // Close the original fd (we don't need two pointers to the same file)
    close(fd);

    // This will now be written to 'log.txt' instead of the screen
    printf("This text is now redirected to the file using dup3!\n");

    return 0;
}