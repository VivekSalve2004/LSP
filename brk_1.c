#include<stdio.h>
#include<unistd.h>

int main()
{
    void *ptr = NULL;

    ptr = sbrk(0);

    printf("Current break value : %p\n",ptr);

    // *(char *) ptr = 'A';            // not recommended 

    return 0;
}