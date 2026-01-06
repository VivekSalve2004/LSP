#include<stdio.h>
#include <sys/resource.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    int iRet = 0;
    int which = PRIO_PGRP;
    id_t who = 0; 

    errno = 0;
    iRet = getpriority(which,who);
    if(iRet == -1 && errno != 0)
    {
        perror("getpriority(PRIO_PGRP) failed");
        exit(1);   
    }
    else
    {
        printf("priority (PRIO_PGRP, caller group) is %d\n",iRet);
    }
    return 0;
}