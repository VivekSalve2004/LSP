/*
 * =======================================================================
 *  Command_ls2.c - Linux ls command implementation with multiple options
 * =======================================================================
 *
 *  Author: [Vivek Salve]
 *  Date: March 28, 2026
 *  Description: A custom implementation of the Linux 'ls' command that supports
 *               various options for listing directory contents. This program
 *               demonstrates low-level system programming using POSIX APIs.
 *
 *  Features:
 *  - Supports multiple ls options: -a, -i, -m, -A, -l, -s
 *  - Uses opendir/readdir/closedir for directory traversal
 *  - Implements stat/lstat for file information
 *  - Color-coded output for different file types
 *  - Proper error handling and permission display
 *
 *  Compilation: gcc Command_ls2.c -o ls2x
 *  Usage: ./ls2x [option]
 *
 *  Options:
 *    (no option)  - List files (default, same as -a)
 *    -a           - List all files including hidden (. and ..)
 *    -i           - List files with inode numbers
 *    -m           - Comma-separated list with color coding
 *    -A           - List all files except . and ..
 *    -l           - Long format listing with full metadata
 *    -s           - Show file sizes in blocks
 *
 * =======================================================================
 */

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

////////////////////////////////////////////////////////////////////////////////
// print_permissions - Convert file mode to permission string
// Converts POSIX file mode bits to a human-readable 10-character string
// showing file type and rwx permissions for user/group/others
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
// print_long - Display file information in long format
// Shows detailed file metadata including permissions, links, owner, group,
// size, modification time, and filename with color coding
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
// list_all_files - Option -a: List all files including hidden
// Lists all directory entries including . and .. (hidden files)
////////////////////////////////////////////////////////////////////////////////
static void list_all_files(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        printf("%s\n", dobj->d_name);
    }
}

////////////////////////////////////////////////////////////////////////////////
// list_with_inodes - Option -i: List files with inode numbers
// Displays inode number followed by filename for each entry
////////////////////////////////////////////////////////////////////////////////
static void list_with_inodes(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        printf("%ld\t%s\n", dobj->d_ino, dobj->d_name);
    }
}

////////////////////////////////////////////////////////////////////////////////
// list_comma_separated - Option -m: Comma-separated list
// Lists files in comma-separated format without color coding
////////////////////////////////////////////////////////////////////////////////
static void list_comma_separated(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        /* Skip hidden files */
        if(dobj->d_name[0] == '.')
            continue;

        printf("%s, ", dobj->d_name);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
// list_all_except_dots - Option -A: List all except . and ..
// Lists all files except the current directory (.) and parent directory (..)
////////////////////////////////////////////////////////////////////////////////
static void list_all_except_dots(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        if(strcmp(dobj->d_name, ".") != 0 && strcmp(dobj->d_name, "..") != 0)
        {
            printf("%s\n", dobj->d_name);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// list_long_format - Option -l: Long format listing
// Displays detailed file information including permissions, ownership,
// size, and modification time with color-coded filenames
////////////////////////////////////////////////////////////////////////////////
static void list_long_format(DIR *dp, const char *path)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        /* Skip hidden files */
        if(dobj->d_name[0] == '.')
            continue;

        print_long(path, dobj->d_name);
    }
}

////////////////////////////////////////////////////////////////////////////////
// list_with_blocks - Option -s: Show file sizes in blocks
// Displays file sizes in 512-byte blocks followed by filename
////////////////////////////////////////////////////////////////////////////////
static void list_with_blocks(DIR *dp, int *total)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        /* Skip hidden files */
        if(dobj->d_name[0] == '.')
            continue;

        struct stat st;
        char fullpath[MAX_BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "./%s", dobj->d_name);

        if(stat(fullpath, &st) == 0)
        {
            printf("%4lld %s\n", (long long)st.st_blocks / 2, dobj->d_name);
            *total += st.st_blocks / 2;
        }
        else
        {
            printf("%s\n", dobj->d_name);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// parse_option - Parse command line arguments
// Converts command line option string to internal option number
////////////////////////////////////////////////////////////////////////////////
static int parse_option(int argc, char *argv[])
{
    if(argc == 1)
    {
        return 1;  // Default: same as -a
    }
    else if(strcmp(argv[1], "-a") == 0)
    {
        return 1;
    }
    else if(strcmp(argv[1], "-i") == 0)
    {
        return 2;
    }
    else if(strcmp(argv[1], "-m") == 0)
    {
        return 3;
    }
    else if(strcmp(argv[1], "-A") == 0)
    {
        return 4;
    }
    else if(strcmp(argv[1], "-l") == 0)
    {
        return 5;
    }
    else if(strcmp(argv[1], "-s") == 0)
    {
        return 6;
    }
    else
    {
        printf("Error: There is no such option\n");
        return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////
// main - Program entry point
// Main function that handles command line parsing and dispatches to appropriate
// listing function based on the selected option
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    int option = parse_option(argc, argv);
    if(option == -1)
    {
        return -1;
    }

    char *path = ".";
    DIR *dp = opendir(path);
    if(dp == NULL)
    {
        printf("Error: Unable to open directory\n");
        return -1;
    }

    int total = 0;

    /* Dispatch to appropriate function based on option */
    switch(option)
    {
        case 1:  /* -a */
            list_all_files(dp);
            break;
        case 2:  /* -i */
            list_with_inodes(dp);
            break;
        case 3:  /* -m */
            list_comma_separated(dp);
            break;
        case 4:  /* -A */
            list_all_except_dots(dp);
            break;
        case 5:  /* -l */
            list_long_format(dp, path);
            break;
        case 6:  /* -s */
            list_with_blocks(dp, &total);
            printf("total %4lld blocks\n", (long long)total);
            break;
    }

    closedir(dp);
    
    return 0;
}