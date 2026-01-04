#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int ret = 0;

    ret = nice(0);
    
    printf("Current nice value : %d\n",ret);

    ret = nice(5);          // Decrease priority

    printf("Current nice value : %d\n",ret);

    return 0;
}