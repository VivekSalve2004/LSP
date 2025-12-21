#include<stdio.h>

int main(int argc , char *argv[])
{
    printf("Inside Command Line Process...\n");

    printf("Command Line Arguments are : \n");

    int i = 0;
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }

    return 0;
}