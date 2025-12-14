#include<stdio.h>
#include<unistd.h>

int main()
{
    int iRet = truncate("Demo.txt" , 10);
    
    if(iRet == 0)
    {
        printf("Truncate is successfull\n");
    }
    else
    {
        printf("There is issue in truncate\n");
    }

    return 0;
}