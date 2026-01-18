#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    int iRet = 0 , iCount =  0 , i = 0;
    char Buffer[1024] = {'\0'};

    fd = open("LB.txt",O_RDONLY);

    while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
    {
        for(i=0;i<iRet;i++)
        {
            if((Buffer[i] >= 'a') && (Buffer[i] <= 'z'))
            {
                iCount++;
            }
        }
    }

    close(fd);
    
    printf("No of small characters : %d \n",iCount);

    return 0;
}