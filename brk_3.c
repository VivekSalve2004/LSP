#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    void *current_break = NULL;

    current_break = sbrk(0);
    
    printf("Current process break %p\n",current_break);

    brk((char *)current_break + 100);

    strcpy((char *)current_break , "Jay Ganesh...");    

    printf("Data from new Memory :  %s\n",(char *)current_break);

    brk(current_break);     // Memory Deallocation

    return 0;
}