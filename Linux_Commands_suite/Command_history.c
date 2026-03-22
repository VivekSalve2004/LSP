// gcc Command_history.c -o historyx
// ./historyx

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024

/*
 * ============================================================
 *  historyx — Print Bash Command History
 * ============================================================
 *
 *  Reads and displays the contents of ~/.bash_history using
 *  low-level Linux system calls: open, read, write, close.
 *
 *  NOTE: Only shows commands saved to disk. Commands from the
 *  current session not yet flushed will NOT appear.
 *
 *  Syscalls used: open, read, write, close
 * ============================================================
 */

// argc = 1
// argv[0] = ./historyx

int main(void)
{
    int      fd;
    ssize_t  iRet;
    char     buffer[SIZE];
    char     path[SIZE];

    /* Build path to ~/.bash_history */
    const char *home = getenv("HOME");
    if (home == NULL)
    {
        fprintf(stderr, "Error : HOME environment variable not set\n");
        return -1;
    }

    snprintf(path, sizeof(path), "%s/.bash_history", home);

    /* Open the history file */
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror(path);
        return -1;
    }

    printf("Reading history using system calls:\n\n");

    /* Read and write to stdout in chunks */
    while ((iRet = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, iRet);
    }

    /* Distinguish EOF (0) from read error (-1) */
    if (iRet == -1)
    {
        perror("read");
        close(fd);
        return -1;
    }

    close(fd);
    
    return 0;
}