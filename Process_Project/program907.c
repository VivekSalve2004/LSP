#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// envp -> environment variable
int main(int argc , char * argv[] , char *envp[])
{
    printf("List of environment variables are : \n");

    int i = 0;

    for(i=0;envp[i] != NULL ; i++)
    {
        printf("%d %s \n",i,envp[i]);
    }
   
    return 0;
}