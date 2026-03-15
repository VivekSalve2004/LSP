#include<stdio.h>

int Addition(int no1,int no2)
{
    int ans = 0;
    ans = no1 + no2;
    return ans;
}

int main()
{
    int Ret = 0 , a = 0 , b = 0;

    printf("Enter first no : \n");
    scanf("%d",&a);

    printf("Enter second no : \n");
    scanf("%d",&b);

    Ret = Addition(a,b);

    printf("Addition is : %d\n",Ret);

    return 0;
}