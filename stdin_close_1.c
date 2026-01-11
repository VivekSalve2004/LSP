#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    char data[1024];
    memset(data,'\0',1024);

    close(0);           // stdin closed

    int fd = open("sample.txt",O_RDONLY);   // ufdt[0] points to sample.txt file 

    scanf("%s",data);                       // now standard input will be taken only from file sample.txt

    printf("%s\n",data);    

    return 0;
}