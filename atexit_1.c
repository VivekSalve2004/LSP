#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void fun()
{
    printf("Inside Fun");
}

void gun()
{
    printf("Inside gun");
}


int main()
{
    printf("Process is created \n");

    atexit(fun);
    atexit(gun);

    _exit(11);
}