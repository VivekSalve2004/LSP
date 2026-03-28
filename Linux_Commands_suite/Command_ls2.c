/*
 * =======================================================================
 *  Command_ls2.c - Linux ls command implementation with multiple options
 * =======================================================================
 *
 *  Author: Vivek Salve
 *  Date: March 28, 2026
 *  Description: A custom implementation of the Linux 'ls' command that supports
 *               24 different options for listing directory contents. This program
 *               demonstrates low-level system programming using POSIX APIs.
 *
 *  Features:
 *  - Supports 24 ls options including sorting, formatting, and display variations
 *  - Uses opendir/readdir/closedir for directory traversal
 *  - Implements stat/lstat for file information and metadata
 *  - Sorting by name, time, size with reverse options
 *  - Recursive directory listing
 *  - Custom long format variations (-h, -n, -g, -o)
 *  - File type indicators (-p, -F)
 *  - Color-coded filenames in long format (-l)
 *  - Proper error handling and permission display
 *
 *  Compilation: gcc Command_ls2.c -o ls2x
 *  Usage: ./ls2x [option]
 *  Options: -a, -i, -m, -A, -l, -s, -r, -t, -S, -u, -c, -R, -d, -p, -F, -h, -n, -g, -o, -1, -x, -Q, -N, -v
 *
 *  Options:
 *    (no option)  - List files (default, same as -a)
 *    -a           - List all files including hidden (. and ..)
 *    -i           - List files with inode numbers
 *    -m           - Comma-separated list
 *    -A           - List all files except . and ..
 *    -l           - Long format listing with full metadata
 *    -s           - Show file sizes in blocks
 *    -r           - Reverse sort by name
 *    -t           - Sort by modification time (newest first)
 *    -S           - Sort by file size (largest first)
 *    -u           - Sort by access time
 *    -c           - Sort by change time
 *    -R           - Recursive directory listing
 *    -d           - List directory itself
 *    -p           - Append / to directory names
 *    -F           - Append type indicators (/ for dir, * for exe, @ for link)
 *    -h           - Human-readable file sizes in long format
 *    -n           - Numeric UID/GID in long format
 *    -g           - Long format without owner column
 *    -o           - Long format without group column
 *    -1           - One file per line
 *    -x           - Sort by name (across columns)
 *    -Q           - Quote filenames
 *    -N           - Raw filenames (no escaping)
 *    -v           - Natural sort by name
 *
 * =======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
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
// FileEntry helper type, collection and sorting support
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    char name[256];
    struct stat st;
} FileEntry;

static int is_hidden_name(const char *name)
{
    return name[0] == '.';
}

static int collect_entries(const char *path, FileEntry entries[], int *count, int include_hidden, int include_dots)
{
    DIR *dp = opendir(path);
    if(dp == NULL)
        return -1;

    struct dirent *dobj;
    *count = 0;

    while((dobj = readdir(dp)) != NULL)
    {
        if(!include_hidden && is_hidden_name(dobj->d_name))
            continue;

        if(!include_dots && (strcmp(dobj->d_name, ".") == 0 || strcmp(dobj->d_name, "..") == 0))
            continue;

        if(*count >= 4096)
            break;

        strncpy(entries[*count].name, dobj->d_name, sizeof(entries[*count].name) - 1);
        entries[*count].name[sizeof(entries[*count].name) - 1] = '\0';

        char fullpath[MAX_BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dobj->d_name);

        if(stat(fullpath, &entries[*count].st) != 0)
            memset(&entries[*count].st, 0, sizeof(entries[*count].st));

        (*count)++;
    }

    closedir(dp);
    return 0;
}

static int compare_name(const void *a, const void *b)
{
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    return strcmp(fa->name, fb->name);
}

static int compare_time_mtime(const void *a, const void *b)
{
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    if(fa->st.st_mtime > fb->st.st_mtime) return -1;
    if(fa->st.st_mtime < fb->st.st_mtime) return 1;
    return strcmp(fa->name, fb->name);
}

static int compare_time_atime(const void *a, const void *b)
{
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    if(fa->st.st_atime > fb->st.st_atime) return -1;
    if(fa->st.st_atime < fb->st.st_atime) return 1;
    return strcmp(fa->name, fb->name);
}

static int compare_time_ctime(const void *a, const void *b)
{
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    if(fa->st.st_ctime > fb->st.st_ctime) return -1;
    if(fa->st.st_ctime < fb->st.st_ctime) return 1;
    return strcmp(fa->name, fb->name);
}

static int compare_size_desc(const void *a, const void *b)
{
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    if(fa->st.st_size > fb->st.st_size) return -1;
    if(fa->st.st_size < fb->st.st_size) return 1;
    return strcmp(fa->name, fb->name);
}

static void list_sorted(const char *path,
                        int include_hidden,
                        int include_dots,
                        int reverse,
                        int (*cmp)(const void *, const void *))
{
    FileEntry entries[4096];
    int count;

    if(collect_entries(path, entries, &count, include_hidden, include_dots) != 0)
    {
        printf("Error: Unable to open directory %s\n", path);
        return;
    }

    qsort(entries, count, sizeof(FileEntry), cmp);

    if(reverse)
    {
        for(int i = count - 1; i >= 0; --i)
            printf("%s\n", entries[i].name);
    }
    else
    {
        for(int i = 0; i < count; ++i)
            printf("%s\n", entries[i].name);
    }
}

static void list_recursive(const char *path)
{
    printf("%s:\n", path);
    FileEntry entries[4096];
    int count = 0;

    if(collect_entries(path, entries, &count, 0, 0) != 0)
    {
        printf("Error: Unable to open directory %s\n", path);
        return;
    }

    for(int i = 0; i < count; ++i)
    {
        printf("%s\n", entries[i].name);
    }

    for(int i = 0; i < count; ++i)
    {
        char fullpath[MAX_BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entries[i].name);
        if(S_ISDIR(entries[i].st.st_mode))
        {
            list_recursive(fullpath);
        }
    }
}

static void list_with_p(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        if(dobj->d_name[0] == '.')
            continue;

        char fullpath[MAX_BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "./%s", dobj->d_name);

        struct stat st;
        if(stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode))
            printf("%s/\n", dobj->d_name);
        else
            printf("%s\n", dobj->d_name);
    }
}

static void list_with_F(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        if(dobj->d_name[0] == '.')
            continue;

        char fullpath[MAX_BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "./%s", dobj->d_name);

        struct stat st;
        if(stat(fullpath, &st) == 0)
        {
            if(S_ISDIR(st.st_mode))
                printf("%s/\n", dobj->d_name);
            else if(S_ISLNK(st.st_mode))
                printf("%s@\n", dobj->d_name);
            else if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                printf("%s*\n", dobj->d_name);
            else
                printf("%s\n", dobj->d_name);
        }
        else
        {
            printf("%s\n", dobj->d_name);
        }
    }
}

static void list_quoted(DIR *dp)
{
    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        if(dobj->d_name[0] == '.')
            continue;
        printf("\"%s\"\n", dobj->d_name);
    }
}

static void list_one_per_line(DIR *dp)
{
    list_all_files(dp);
}

static void list_with_nat_sort(const char *path)
{
    list_sorted(path, 0, 0, 0, compare_name);
}

static void print_long_custom(const char *dirpath, const char *name, int mode)
{
    char fullpath[MAX_BUFFER_SIZE];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, name);

    struct stat st;
    if(lstat(fullpath, &st) == -1)
    {
        fprintf(stderr, "ls2x: stat '%s': %s\n", fullpath, strerror(errno));
        return;
    }

    print_permissions(st.st_mode);
    printf(" %2lu", (unsigned long)st.st_nlink);

    if(mode == 2) // no owner
    {
        printf(" %-8s", "");
    }
    else if(mode == 4) // numeric id
    {
        printf(" %-8u", (unsigned)st.st_uid);
    }
    else
    {
        struct passwd *pw = getpwuid(st.st_uid);
        if(pw)
            printf(" %-8s", pw->pw_name);
        else
            printf(" %-8u", (unsigned)st.st_uid);
    }

    if(mode == 3) // no group
    {
        printf(" %-8s", "");
    }
    else if(mode == 4) // numeric id
    {
        printf(" %-8u", (unsigned)st.st_gid);
    }
    else
    {
        struct group *gr = getgrgid(st.st_gid);
        if(gr)
            printf(" %-8s", gr->gr_name);
        else
            printf(" %-8u", (unsigned)st.st_gid);
    }

    if(mode == 8) // human readable
    {
        double sz = (double)st.st_size;
        const char *units[] = {"B", "K", "M", "G", "T"};
        int ui = 0;
        while(sz >= 1024 && ui < 4) { sz /= 1024; ui++; }
        printf(" %6.1f%s", sz, units[ui]);
    }
    else
    {
        printf(" %8lld", (long long)st.st_size);
    }

    char timebuf[32];
    struct tm *tm_info;
    if(mode == 16)
        tm_info = localtime(&st.st_atime);
    else if(mode == 32)
        tm_info = localtime(&st.st_ctime);
    else
        tm_info = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
    printf(" %s", timebuf);

    if(S_ISDIR(st.st_mode))
        printf(" %s\n", name);
    else
        printf(" %s\n", name);
}

static void list_long_custom_format(const char *path, int mode)
{
    DIR *dp = opendir(path);
    if(dp == NULL)
    {
        printf("Error: Unable to open directory %s\n", path);
        return;
    }

    struct dirent *dobj;
    while((dobj = readdir(dp)) != NULL)
    {
        if(dobj->d_name[0] == '.')
            continue;

        print_long_custom(path, dobj->d_name, mode);
    }

    closedir(dp);
}

////////////////////////////////////////////////////////////////////////////////
// parse_option - Parse command line arguments
// Converts command line option string to internal option number
////////////////////////////////////////////////////////////////////////////////
static int parse_option(int argc, char *argv[])
{
    if(argc == 1)
        return 1;

    if(strcmp(argv[1], "-a") == 0) return 1;
    if(strcmp(argv[1], "-i") == 0) return 2;
    if(strcmp(argv[1], "-m") == 0) return 3;
    if(strcmp(argv[1], "-A") == 0) return 4;
    if(strcmp(argv[1], "-l") == 0) return 5;
    if(strcmp(argv[1], "-s") == 0) return 6;
    if(strcmp(argv[1], "-r") == 0) return 7;
    if(strcmp(argv[1], "-t") == 0) return 8;
    if(strcmp(argv[1], "-S") == 0) return 9;
    if(strcmp(argv[1], "-u") == 0) return 10;
    if(strcmp(argv[1], "-c") == 0) return 11;
    if(strcmp(argv[1], "-R") == 0) return 12;
    if(strcmp(argv[1], "-d") == 0) return 13;
    if(strcmp(argv[1], "-p") == 0) return 14;
    if(strcmp(argv[1], "-F") == 0) return 15;
    if(strcmp(argv[1], "-h") == 0) return 16;
    if(strcmp(argv[1], "-n") == 0) return 17;
    if(strcmp(argv[1], "-g") == 0) return 18;
    if(strcmp(argv[1], "-o") == 0) return 19;
    if(strcmp(argv[1], "-1") == 0) return 20;
    if(strcmp(argv[1], "-x") == 0) return 21;
    if(strcmp(argv[1], "-Q") == 0) return 22;
    if(strcmp(argv[1], "-N") == 0) return 23;
    if(strcmp(argv[1], "-v") == 0) return 24;

    printf("Error: There is no such option\n");
    return -1;
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
        return -1;

    char *path = ".";
    DIR *dp = opendir(path);
    if(dp == NULL)
    {
        printf("Error: Unable to open directory\n");
        return -1;
    }

    int total = 0;

    switch(option)
    {
        case 1:
            list_all_files(dp);
            break;
        case 2:
            list_with_inodes(dp);
            break;
        case 3:
            list_comma_separated(dp);
            break;
        case 4:
            list_all_except_dots(dp);
            break;
        case 5:
            list_long_format(dp, path);
            break;
        case 6:
            list_with_blocks(dp, &total);
            printf("total %4lld blocks\n", (long long)total);
            break;
        case 7:
            list_sorted(path, 0, 0, 1, compare_name);
            break;
        case 8:
            list_sorted(path, 0, 0, 0, compare_time_mtime);
            break;
        case 9:
            list_sorted(path, 0, 0, 0, compare_size_desc);
            break;
        case 10:
            list_sorted(path, 0, 0, 0, compare_time_atime);
            break;
        case 11:
            list_sorted(path, 0, 0, 0, compare_time_ctime);
            break;
        case 12:
            closedir(dp);
            list_recursive(path);
            return 0;
        case 13:
            printf("%s\n", path);
            break;
        case 14:
            list_with_p(dp);
            break;
        case 15:
            list_with_F(dp);
            break;
        case 16:
            list_long_custom_format(path, 8);  // human readable file sizes
            break;
        case 17:
            list_long_custom_format(path, 4);  // numeric ids for owner/group
            break;
        case 18:
            list_long_custom_format(path, 2);  // no owner column
            break;
        case 19:
            list_long_custom_format(path, 3);  // no group column
            break;
        case 20:
            list_one_per_line(dp);
            break;
        case 21:
            list_sorted(path, 0, 0, 0, compare_name);  // column-like default
            break;
        case 22:
            list_quoted(dp);
            break;
        case 23:
            list_all_files(dp);
            break;
        case 24:
            list_with_nat_sort(path);
            break;
        default:
            printf("Error: Unknown option number %d\n", option);
            break;
    }

    closedir(dp);

    return 0;
}