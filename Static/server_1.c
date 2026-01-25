// gcc server_1.c -L. libclient_1.a -o server_1

#include<stdio.h>
#include<stdlib.h>

int Addition(int A,int B);
int Substraction(int A,int B);

int main()
{
    int iRet = 0;

    iRet = Addition(11,10);
    printf("Addition is : %d\n",iRet);

    iRet = Substraction(11,10);
    printf("Substraction is : %d\n",iRet);

    return 0;
}