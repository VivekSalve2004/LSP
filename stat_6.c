#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    struct stat sobj;

    int iRet = stat("./LSPL.txt",&sobj);

    printf("Inode number : %lu\n",sobj.st_ino);
    printf("Hard Links : %lu\n",sobj.st_nlink);
    printf("Total File Size : %lu\n",sobj.st_size);
    printf("Block Size : %lu\n",sobj.st_blksize);

    printf("File type is : %d\n",sobj.st_mode);

    return 0;
}