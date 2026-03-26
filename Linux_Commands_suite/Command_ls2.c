// gcc Command_ls2.c -o ls2x
// ./ls2x
// ./ls2x -a
// ./ls2x -i
// ./ls2x -m

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 1024

/*
 * ============================================================
 *  ls2x — List Directory Contents (with options)
 * ============================================================
 *
 *  Lists all entries in the current directory using
 *  low-level Linux directory syscalls: opendir, readdir,
 *  closedir.
 *
 *  Usage:
 *    ./ls2x         list all files (default)
 *    ./ls2x -a      list all files including hidden (. and ..)
 *    ./ls2x -i      list all files with inode numbers
 *    ./ls2x -m      list files comma-separated with colour coding
 *                   (blue = directory, green = executable)
 *
 *  Options:
 *    option = 1 → ls -a  (print filename only, shows hidden)
 *    option = 2 → ls -i  (print inode number + filename)
 *    option = 3 → ls -m  (comma-separated, colour-coded, no hidden)
 *
 *  NOTE:
 *    -a and -i show ALL entries including hidden files (. and ..)
 *    -m hides dotfiles to match real ls -m behaviour
 *    -m uses ANSI colour codes — requires a colour-capable terminal
 *
 *  Syscalls used: opendir, readdir, closedir, stat
 * ============================================================
 */

// argc = 1  →  ./ls2x
// argc = 2  →  ./ls2x -a  OR  ./ls2x -i  OR  ./ls2x -m
//              argv[0]         argv[1]

int main(int argc, char *argv[])
{
    int option = 0;
    // option = 1 : ls -a (filenames only, includes hidden)
    // option = 2 : ls -i (inode number + filename)
    // option = 3 : ls -m (comma-separated, colour-coded, no dotfiles)

    option = argc;

    if(argc == 1)
    {
        option = 1;
    }
    else if(strcmp(argv[1], "-a") == 0)
    {
        option = 1;
    }
    else if(strcmp(argv[1], "-i") == 0)
    {
        option = 2;
    }
    else if(strcmp(argv[1], "-m") == 0)
    {
        option = 3;
    }
    else if(strcmp(argv[1], "-A") == 0)
    {
        option = 4;
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
    if(dp == NULL)
    {
        printf("Error : Unable to open directory\n");
        return -1;
    }

    struct dirent *dobj;

    /* Read and print each directory entry based on option */
    while((dobj = readdir(dp)) != NULL)
    {
        if(option == 1)
        {
            /* -a : print filename only (includes . and ..) */
            printf("%s\n", dobj->d_name);
        }
        if(option == 2)
        {
            /* -i : print inode number followed by filename */
            printf("%ld\t%s\n", dobj->d_ino, dobj->d_name);
        }
        if(option == 3)
        {
            /* -m : comma-separated, colour-coded, skip hidden files */
            if(dobj->d_name[0] == '.')
                continue;

            struct stat st;
            char fullpath[MAX_BUFFER_SIZE];
            snprintf(fullpath, sizeof(fullpath), "./%s", dobj->d_name);

            if(stat(fullpath, &st) == 0)
            {
                if(S_ISDIR(st.st_mode))
                {
                    /* Directory — blue */
                    printf("\033[1;34m%s\033[0m, ", dobj->d_name);
                }
                else if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                {
                    /* Executable — green */
                    printf("\033[1;32m%s\033[0m, ", dobj->d_name);
                }
                else
                {
                    /* Regular file — no colour */
                    printf("%s, ", dobj->d_name);
                }
            }
            else
            {
                /* stat failed — print name without colour */
                printf("%s, ", dobj->d_name);
            }
        }
        if(option == 4)
        {
            if(strcmp(dobj->d_name, ".") != 0 && strcmp(dobj->d_name, "..") != 0)
            {
                printf("%s\n", dobj->d_name);
            }
        }
    }

    printf("\n");
    
    closedir(dp);

    return 0;
}