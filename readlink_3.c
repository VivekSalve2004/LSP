#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    char Path[100];
    memset(Path , '\0' , sizeof(Path));
    int fd = 0;
    char Arr[20];
    memset(Arr,'\0',sizeof(Arr));

    int iRet = readlink("./test/LSPl.txt" , Path , sizeof(Path));
    
    if(iRet == -1)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    Path[iRet] = '\0';
    printf("Data from readlink is : %s\n" , Path);
    printf("No of Bytes read : %d\n",iRet);

    fd = open(Path , O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file : \n");
        return -1;
    }

    read(fd , Arr , 10);

    printf("Data from original file is : %s\n",Arr);

    close(fd);

    return 0;
}