#include<stdio.h>

int main(int argc , char *argv[])
{
    printf("No of command line arguments are : %d\n",argc);    

    printf("Executable name : %s \n",argv[0]);
    printf("IP Address : %s \n",argv[1]);
    printf("Port No : %s \n",argv[2]);
    printf("Targeted File : %s \n",argv[3]);
    printf("New File name : %s \n",argv[4]);

    return 0;
}