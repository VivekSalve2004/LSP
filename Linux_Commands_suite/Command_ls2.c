// gcc Command_ls2.c -o lsx
// ./lsx
// ./lsx -a
// ./lsx -i

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAX_BUFFER_SIZE 1024

/*
 * ============================================================
 *  lsx — List Directory Contents (with options)
 * ============================================================
 *
 *  Lists all entries in the current directory using
 *  low-level Linux directory syscalls: opendir, readdir,
 *  closedir.
 *
 *  Usage:
 *    ./lsx         list all files (default)
 *    ./lsx -a      list all files including hidden (same as default)
 *    ./lsx -i      list all files with inode numbers
 *
 *  Options:
 *    option = 1 → ls -a  (print filename only)
 *    option = 2 → ls -i  (print inode number + filename)
 *
 *  NOTE: Both modes show hidden files (entries starting with '.')
 *  including '.' (current dir) and '..' (parent dir).
 *
 *  Syscalls used: opendir, readdir, closedir
 * ============================================================
 */

// argc = 1  →  ./lsx
// argc = 2  →  ./lsx -a  OR  ./lsx -i
//              argv[0]        argv[1]

int main(int argc, char *argv[])
{
    int option = 0;
    // option = 1 : ls -a (filenames only)
    // option = 2 : ls -i (inode + filename)

    option = argc;

    if (argc == 1)
    {
        option = 1;
    }
    else if (strcmp(argv[1], "-a") == 0)
    {
        option = 1;
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        option = 2;
    }
    else
    {
        printf("Error : There is no such option\n");
        return -1;
    }

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

    /* Read and print each directory entry based on option */
    while ((dobj = readdir(dp)) != NULL)
    {
        if (option == 1)
        {
            /* -a : print filename only */
            printf("%s\n", dobj->d_name);
        }
        if (option == 2)
        {
            /* -i : print inode number followed by filename */
            printf("%ld\t%s\n", dobj->d_ino, dobj->d_name);
        }
    }

    closedir(dp);

    return 0;
}