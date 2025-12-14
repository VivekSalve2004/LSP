#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    int iRet = symlink("DemoX.txt" , "Hello.txt");

    if(iRet == 0)
    {
        printf("Symbolic link is successful\n");
    }
    else
    {
        printf("%s\n",strerror(errno));
    }

    return 0;
}