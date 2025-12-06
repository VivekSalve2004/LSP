#include<stdio.h>

int main(int argc , char *argv[])
{
    printf("Number of Command line args are : %d\n",argc);

    for(int iCnt = 0;iCnt<argc;iCnt++)
    {
        printf("%s\n" , argv[iCnt]);
    }
    
    return 0;
}