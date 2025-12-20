#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    int iRet = link("./Demo.txt" , "./test/Demo.txt");

    if(iRet == 0)
    {
        printf("link is successful\n");
    }

    return 0;
}