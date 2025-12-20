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
    struct dirent *ptr = NULL;
    
    dp = opendir("./Data");             // read only 

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }
    
    printf("Directory gets successfully opened \n");
    
    ptr = readdir(dp);
    
    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    ptr = readdir(dp);

    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    ptr = readdir(dp);

    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    ptr = readdir(dp);

    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    ptr = readdir(dp);

    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    ptr = readdir(dp);

    printf("Inode Number : %ld\n",ptr->d_ino);
    printf("File Name: %s\n",ptr->d_name);

    return 0;
}