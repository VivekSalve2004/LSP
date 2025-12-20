#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    char Arr[100];

    int fd = open("./process.txt" , O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file \n");
        return -1;
    }

    int iRet = rename("./process.txt","./test/Hello.txt");      // Same inode no different name
    
    if(iRet == 0)
    {
        printf("Rename Successful \n");
    }
    else
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    iRet = read(fd , Arr , 50);

    if(iRet != 0)
    {
        printf("Data from file is : %s\n",Arr);
    }

    close(fd);

    return 0;
}