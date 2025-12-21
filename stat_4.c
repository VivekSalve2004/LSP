#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
    struct stat sobj;

    int iRet = stat("Demo.txt",&sobj);

    printf("Inode number : %lu\n",sobj.st_ino);
    printf("Hard Links : %lu\n",sobj.st_nlink);
    printf("Total File Size : %lu\n",sobj.st_size);
    printf("Block Size : %lu\n",sobj.st_blksize);

    printf("File type is : %d\n",sobj.st_mode);

    if(S_ISBLK(sobj.st_mode))
    {
        printf("Block Device\n");
    }
    else if(S_ISCHR(sobj.st_mode))
    {
        printf("Character Device\n");
    }
    else if(S_ISDIR(sobj.st_mode))
    {
        printf("Directorry File\n");
    }
    else if(S_ISREG(sobj.st_mode))
    {
        printf("Regular File\n");
    }
    else if(S_ISSOCK(sobj.st_mode))
    {
        printf("Socket File\n");
    }
    else if(S_ISFIFO(sobj.st_mode))
    {
        printf("PIPE File\n");
    }
    else if(S_ISLNK(sobj.st_mode))
    {
        printf("Symbolic Link File\n");
    }

    return 0;
}