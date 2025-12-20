#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

// Error File 
// Too Few Arguments

int main()
{
    printf("Current Directory Name : %s\n",getcwd());
    
    return 0;
}