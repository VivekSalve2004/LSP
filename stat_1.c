#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    struct stat sobj;

    int iRet = stat("Demo.txt",&sobj);

    if(iRet == 0)
    {
        printf("Stat works successfully \n");
    }
    else
    {
        printf("There is issue in stat\n");
        return -1;
    }

    return 0;
}