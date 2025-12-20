#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
    int iRet = rename("DemoX.txt","Demo.txt");      // only updated directory file entry not inode entry

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