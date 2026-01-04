#include<stdio.h>
#include<string.h>
#include<sys/mman.h>

int main()
{
    char *ptr = NULL;

    ptr = mmap(NULL , 4096 , PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS , -1 , 0);

    strcpy(ptr , "Jay Ganesh...");

    printf("Data from Mapped Memory is : %s\n",ptr);

    munmap(ptr , 4096);

    return 0;
}