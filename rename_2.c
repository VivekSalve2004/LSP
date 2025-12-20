#include<stdio.h>
#include<string.h>
#include<errno.h>

int main()
{
    int iRet = rename("./Demo.txt","./December.txt");      // ./ current working directory of process (./myexe)
    if(iRet == 0)
    {
        printf("Rename Successful \n");
    }
    else
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    return 0;
}