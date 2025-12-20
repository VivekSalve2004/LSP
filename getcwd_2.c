#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

// Error File 
// Too Few Arguments

int main()
{
    char Arr[50];

    memset(Arr,'\0',sizeof(Arr)); 

    getcwd(Arr , sizeof(Arr));
    
    printf("Current Directory Name : %s\n",Arr);

    return 0;
}