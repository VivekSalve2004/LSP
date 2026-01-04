#include<stdio.h>
#include<unistd.h>

int main()
{
    void *ptr = NULL;

    ptr = sbrk(100);                // ptr = malloc(100)

    printf("Current break value : %p\n",ptr);

    ptr = sbrk(0);

    printf("Current break value : %p\n",ptr);

    ptr = sbrk(-100);               // free(ptr)

    printf("Current break value : %p\n",ptr);

    ptr = sbrk(0);

    printf("Current break value : %p\n",ptr);


    return 0;
}