// gcc Command_ls2.c -o ls2x
// ./ls2x
// ./ls2x -a
// ./ls2x -i
// ./ls2x -m
// ./ls2x -A
// ./ls2x -l

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

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
 *    ./ls2x -A      list all files excluding . and ..
 *    ./ls2x -l      long format listing
 *                   (permissions, links, owner, group, size, time, name)
 *
 *  Options:
 *    option = 1 → ls -a  (print filename only, shows hidden)
 *    option = 2 → ls -i  (print inode number + filename)
 *    option = 3 → ls -m  (comma-separated, colour-coded, no hidden)
 *    option = 4 → ls -A  (all files except . and ..)
 *    option = 5 → ls -l  (long format with full file metadata)
 *
 *  NOTE:
 *    -a and -i show ALL entries including hidden files (. and ..)
 *    -A shows hidden files but skips . and ..
 *    -m hides dotfiles to match real ls -m behaviour
 *    -m and -l use ANSI colour codes — requires colour-capable terminal
 *    -l uses lstat() so symlinks show as 'l' not their target type
 *
 *  Syscalls used: opendir, readdir, closedir, stat, lstat
 *  Library calls: getpwuid, getgrgid, localtime, strftime
 * ============================================================
 */

// argc = 1  →  ./ls2x
// argc = 2  →  ./ls2x -a  OR  ./ls2x -i  OR  ./ls2x -m
//           →  ./ls2x -A  OR  ./ls2x -l
//              argv[0]         argv[1]

/* ------------------------------------------------------------------ */
/*  Print permission bits as 10-char string  e.g.  drwxr-xr-x         */
/* ------------------------------------------------------------------ */
static void print_permissions(mode_t mode)
{
    /* File type character */
    if      (S_ISDIR(mode))  printf("d");
    else if (S_ISLNK(mode))  printf("l");
    else if (S_ISCHR(mode))  printf("c");
    else if (S_ISBLK(mode))  printf("b");
    else if (S_ISFIFO(mode)) printf("p");
    else if (S_ISSOCK(mode)) printf("s");
    else                      printf("-");

    /* User (owner) permissions */
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    /* Group permissions */
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    /* Others permissions */
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

/* ------------------------------------------------------------------ */
/*  Print one entry in long format (-l)                                 */
/*                                                                      */
/*  Output format:                                                      */
/*  -rw-r--r--  1 vivek    vivek       1234 Jan 01 12:00 file.c        */
/*  │           │ │        │           │    │             └─ filename   */
/*  │           │ │        │           │    └─ modification time        */
/*  │           │ │        │           └─ size in bytes                 */
/*  │           │ │        └─ group name                                */
/*  │           │ └─ owner name                                         */
/*  │           └─ hard link count                                      */
/*  └─ permissions (type + rwx for user/group/others)                  */
/* ------------------------------------------------------------------ */
static void print_long(const char *dirpath, const char *name)
{
    char fullpath[MAX_BUFFER_SIZE];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, name);

    struct stat st;

    /* lstat used instead of stat so symlinks report as 'l' type       */
    if(lstat(fullpath, &st) == -1)
    {
        fprintf(stderr, "ls2x: stat '%s': %s\n", fullpath, strerror(errno));
        return;
    }

    /* 1. Permissions */
    print_permissions(st.st_mode);

    /* 2. Hard link count */
    printf(" %2lu", (unsigned long)st.st_nlink);

    /* 3. Owner name (falls back to UID number if name not found) */
    struct passwd *pw = getpwuid(st.st_uid);
    if(pw)
        printf(" %-8s", pw->pw_name);
    else
        printf(" %-8u", (unsigned)st.st_uid);

    /* 4. Group name (falls back to GID number if name not found) */
    struct group *gr = getgrgid(st.st_gid);
    if(gr)
        printf(" %-8s", gr->gr_name);
    else
        printf(" %-8u", (unsigned)st.st_gid);

    /* 5. File size in bytes */
    printf(" %8lld", (long long)st.st_size);

    /* 6. Last modification time — format: Jan 01 12:00 */
    char timebuf[32];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
    printf(" %s", timebuf);

    /* 7. Filename — colour coded by type */
    if(S_ISDIR(st.st_mode))
        printf(" \033[1;34m%s\033[0m\n", name);    /* blue  : directory  */
    else if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
        printf(" \033[1;32m%s\033[0m\n", name);    /* green : executable */
    else
        printf(" %s\n", name);                      /* white : regular    */
}

/* ------------------------------------------------------------------ */
/*  main                                                                */
/* ------------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    int option = 0;
    // option = 1 : ls -a (filenames only, includes hidden)
    // option = 2 : ls -i (inode number + filename)
    // option = 3 : ls -m (comma-separated, colour-coded, no dotfiles)
    // option = 4 : ls -A (all except . and ..)
    // option = 5 : ls -l (long format with full metadata)

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
    else if(strcmp(argv[1], "-l") == 0)
    {
        option = 5;
    }
    else if(strcmp(argv[1], "-s") == 0)
    {
        option = 6;
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
    int total = 0;
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
            /* -A : skip . and .. but show all other hidden files */
            if(strcmp(dobj->d_name, ".") != 0 && strcmp(dobj->d_name, "..") != 0)
            {
                printf("%s\n", dobj->d_name);
            }
        }
        if(option == 5)
        {
            /* -l : long format, skip hidden files */
            if(dobj->d_name[0] == '.')
                continue;

            print_long(path, dobj->d_name);
        }
        if(option == 6)
        {
            if(dobj->d_name[0] == '.')
                continue;
            struct stat st;
            char fullpath[MAX_BUFFER_SIZE];
            snprintf(fullpath, sizeof(fullpath), "./%s", dobj->d_name);
            if(stat(fullpath, &st) == 0)
            {
                printf("%4lld %s\n", (long long)st.st_blocks / 2, dobj->d_name);
                total += st.st_blocks / 2;
            }
            else
            {
                printf("%s\n", dobj->d_name);
            }   
        }
    }

    printf("total %4lld blocks \n", (long long)total);

    printf("\n");

    closedir(dp);

    return 0;
}