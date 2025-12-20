#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    char Path[100];
    memset(Path , '\0' , sizeof(Path));

    int iRet = readlink("./test/LSPl.txt" , Path , sizeof(Path));
    
    if(iRet == -1)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    Path[iRet] = '\0';
    printf("Data from readlink is : %s\n" , Path);
    printf("No of Bytes read : %d\n",iRet);

    return 0;
}