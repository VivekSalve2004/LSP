#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>               // for DIR

int main()
{
    DIR *dp = NULL;
    
    dp = opendir("./Data");             // read only 

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory gets successfully opened \n");
    }

    return 0;
}