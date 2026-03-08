#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void ShowProcessInformation(int pid)
{
    FILE * fp = NULL;
    char line[80];
    char filename[100];

    sprintf(filename , "/proc/%d/status",pid);

    printf("Accesing the file : %s\n",filename);

    fp = fopen(filename , "r");

    if(fp == NULL)
    {
        printf("Error : Unable to access system file \n");
        return ;
    }

    printf("========================================================================================\n");
    printf("================================= Process Information ==================================\n");
    printf("========================================================================================\n");
    
    while(fgets(line , sizeof(line) , fp) != NULL)
    {
        printf("%s \n",line);
    }

    printf("========================================================================================\n");
    

}

int main()
{
    int pid = 0;

    printf("========================================================================================\n");
    printf("================================== Process Inspector ===================================\n");
    printf("========================================================================================\n");

    printf("Enter the pid of a process that you want to inspect \n");

    scanf("%d",&pid);

    if(pid <= 0)
    {
        printf("INVALID PID \n");
        return -1;
    }

    ShowProcessInformation(pid);

    return 0;
}