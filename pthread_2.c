#include<stdio.h>

void Demo(int *ptr)
{
    *ptr = 11;
    *(ptr+1) = 21;      
}

int main()
{
    int Arr[2];

    Demo(Arr);

    printf("Return value is : %d %d\n",Arr[0],Arr[1]);

    return 0;
}