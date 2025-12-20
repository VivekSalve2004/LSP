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
    char Path[50];

    getcwd(Path , sizeof(Path));

    printf("Current Directory Name : %s\n",Path);

    chdir("./Data");

    getcwd(Path , sizeof(Path));
    printf("Current Directory Name :  %s\n",Path);

    // open();

    return 0;
}