#include<stdio.h>
#include <sys/resource.h>
#include<stdlib.h>

int main()
{
    int iRet = 0;
    int which = PRIO_PGRP;
    id_t who = 0; 
    int new_priority = 5;

    iRet = setpriority(which,who,new_priority);
    if(iRet == -1)
    {
        perror("setpriority(PRIO_PGRP) failed");
        exit(1);   
    }
    else
    {
        printf("priority (PRIO_PGRP, caller group) is %d\n",iRet);
    }
    return 0;
}