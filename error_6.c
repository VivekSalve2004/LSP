#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = open("example.txt",O_RDONLY | O_CREAT,0664);
    printf("FD value : %d\n",fd);
    if(errno != 0)
    {
        switch(errno)
        {
            case ENOENT:
            printf("There is no such file. Create the file and open it\n");
            break;

            case EACCES:
            printf("Unable to access as there is no permission\n");
            break;

            default:
            printf("%s\n",strerror(errno));
        }
    }

    return 0;
}