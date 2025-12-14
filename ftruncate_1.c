#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = open("Demo.txt" , O_RDONLY);

    int iRet = ftruncate(fd , 5);
    
    if(iRet == 0)
    {
        printf("Truncate is successfull\n");
    }
    else
    {
        printf("There is issue in truncate\n");
    }

    return 0;
}