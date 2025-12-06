#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd = creat("LSP.txt",0777);

    if(fd == -1)
    {
        printf("unable to create file \n");
    }
    else
    {
        printf("Files gets succesfully created with fd : %d\n",fd);
    }
    close(fd);
    return 0;
}