// gcc Command_ls.c -o lsx
// ./lsx

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAX_BUFFER_SIZE 1024

/*
 * ============================================================
 *  lsx — List Directory Contents
 * ============================================================
 *
 *  Lists all entries in the current directory using
 *  low-level Linux directory syscalls: opendir, readdir,
 *  closedir.
 *
 *  NOTE: Also shows hidden files (entries starting with '.')
 *  including '.' (current dir) and '..' (parent dir).
 *
 *  Syscalls used: opendir, readdir, closedir
 * ============================================================
 */

// argc = 1
// argv[0] = ./lsx

int main(int argc, char *argv[])
{
    char *path = ".";
    DIR  *dp   = NULL;

    /* Open current directory */
    dp = opendir(path);
    if (dp == NULL)
    {
        printf("Error : Unable to open directory\n");
        return -1;
    }

    struct dirent *dobj;

    /* Read and print each directory entry */
    while ((dobj = readdir(dp)) != NULL)
    {
        printf("%s\n", dobj->d_name);
    }

    closedir(dp);

    return 0;
}