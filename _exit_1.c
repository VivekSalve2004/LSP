#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    printf("Process is created \n");

    _exit(11);
}