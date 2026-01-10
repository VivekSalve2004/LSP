// Named pipe Client X

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main()
{
    int fd = 0;
    int iRet = 0;
    char Arr[100] = {'\0'};
    
    fd = open("/tmp/marvellous",O_RDONLY);

    if(fd == -1)
    {
        printf("Unable to open named pipe \n");
        return -1;
    }

    read(fd , Arr , 3);

    printf("Data gets successfully read from the pipe by the \n");
    printf("Data is : %s\n",Arr);

    close(fd);

    return 0;
}