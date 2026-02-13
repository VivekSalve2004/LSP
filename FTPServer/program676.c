#include<stdio.h>

int main(int argc , char *argv[])
{
    printf("No of command line arguments are : %d\n",argc);    

    if(argc != 5)
    {
        printf("Unable to proceed as invalid no of arguments \n");
        printf("Please provide : \n");
        printf("IP Address\nPort No\nTargeted File name\nNew File name\n");
        return -1;
    }
    printf("Executable name : %s \n",argv[0]);
    printf("IP Address : %s \n",argv[1]);
    printf("Port No : %s \n",argv[2]);
    printf("Targeted File : %s \n",argv[3]);
    printf("New File name : %s \n",argv[4]);

    return 0;
}