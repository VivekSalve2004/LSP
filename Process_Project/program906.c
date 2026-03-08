#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// ./myexe 11 21 
int main(int argc , char * argv[])
{
    int ans = 0;

    if(argc != 3)
    {
        printf("Usage : ./myexe <no1> <no2> \n");
        return -1;
    }

    ans = atoi(argv[1]) + atoi(argv[2]);

    printf("Addition is : %d\n",ans);
   
    return 0;
}