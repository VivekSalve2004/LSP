#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd = open("Demo.txt",O_CREAT | O_WRONLY | O_APPEND , 0777);
    char Buffer[] = "indiaismycountry";
    int iRet = 0;
    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason  : %s\n",strerror(errno));
        return -1;
    }

    printf("File succesfully opened with fd : %d\n",fd);
    
    iRet = write(fd,Buffer,16);                 //Overwrite issue
    printf("%d bytes gets written\n",iRet);

    fsync(fd);                                  // Process is in Waiting state 

    close(fd);

    return 0;
}