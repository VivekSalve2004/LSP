#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    FILE * fp = NULL;
    char Buffer[256];
    fp = fopen("/proc/meminfo","r");

    if(fp == NULL)
    {
        printf("Error : Unable to open file \n");
        return -1;
    }

    printf("========================================================================================\n");
    printf("==================================== Memory Scanner ====================================\n");
    printf("========================================================================================\n");

    while(fgets(Buffer , sizeof(Buffer) , fp) != NULL)
    {
        printf("%s \n",Buffer);
    }

    printf("========================================================================================\n");

    fclose(fp);

    return 0;
}