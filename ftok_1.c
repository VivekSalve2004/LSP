#include<stdio.h>
#include<sys/ipc.h>

int main()
{
    key_t key;

    key = ftok("LSP.txt",'s');

    printf("KEY is : %d\n",key);

    return 0;
}