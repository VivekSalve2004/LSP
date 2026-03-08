#include<stdio.h>
#include<unistd.h>

int main(int argc , char * argv[])
{
    int i = 0;

    printf("Commmand line arguments are : \n");

    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }

    
   
    return 0;
}