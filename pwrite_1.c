#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    int fd = 0;
    off_t offset = 0;
    char Buffer[100] = "Pune";
    
    fd = open("./LSP.txt" , O_WRONLY | O_APPEND);

    int iRet = pwrite(fd , Buffer , 4 , 10);

    offset = lseek(fd , 0 , SEEK_CUR);
    printf("Current offset is : %ld\n",offset);    // 15

    return 0;
}