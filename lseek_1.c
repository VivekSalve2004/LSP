#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
// lseek works on regular files only 
#define SIZE_OF_BUFFER 100

int main()
{
    int fd = open("Demo.txt",O_RDONLY);
    char Buffer[SIZE_OF_BUFFER];
    int iRet = 0;

    memset(Buffer,'\0',SIZE_OF_BUFFER);                 

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason  : %s\n",strerror(errno));
        return -1;
    }

    printf("File succesfully opened with fd : %d\n",fd);
    
    iRet = lseek(fd , 10 , SEEK_CUR);

    printf("Updated file offset is : %d\n",iRet);

    close(fd);

    return 0;
}