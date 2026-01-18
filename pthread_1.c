#include<stdio.h>

void Demo(int *ptr)
{
    *ptr = 11;      
}

int main()
{
    int no = 0;

    Demo(&no);

    printf("Return value is : %d\n",no);

    return 0;
}