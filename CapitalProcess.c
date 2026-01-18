#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    int iRet = 0 , iCount =  0 , i = 0;
    char Buffer[1024] = {'\0'};

    fd = open("PPA.txt",O_RDONLY);

    while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
    {
        for(i=0;i<iRet;i++)
        {
            if((Buffer[i] >= 'A') && (Buffer[i] <= 'Z'))
            {
                iCount++;
            }
        }
    }

    close(fd);
    
    printf("No of capital characters : %d \n",iCount);

    return 0;
}