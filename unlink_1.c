#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    int iRet = unlink("demo.txt");

    if(iRet == 0)
    {
        printf("Unlink is successful\n");
    }

    return 0;
}