#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    void *current_break = NULL;
    void *new_break = NULL;

    current_break = sbrk(0);
    
    printf("Current process break %p\n",current_break);

    new_break = sbrk(100);

    strcpy((char *)new_break , "Jay Ganesh...");    

    printf("Data from new Memory :  %s",(char *)new_break);

    sbrk(-100);

    return 0;
}