#include<stdio.h>
#include <sys/resource.h>
#include<stdlib.h>

int main()
{
    int iRet = 0;
    int which = PRIO_PROCESS;
    id_t who = 0; 

    int errno = 0;
    iRet = getpriority(which,who);
    if(iRet != -1)
    {
        printf("Priority of current process is %d\n",iRet);
    }
    else
    {
        perror("getpriority(PRIO_PROCESS) failed");
        exit(1);
    }

    return 0;
}