#include<stdio.h>
#include <sys/resource.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    int iRet = 0;
    int which = PRIO_USER;
    id_t who = 0; 

    errno = 0;
    iRet = getpriority(which,who);
    if(iRet == -1 && errno != 0)
    {
        perror("getpriority(PRIO_USER) failed");
        exit(1);   
    }
    else
    {
        printf("priority (PRIO_USER, caller UID) is %d\n",iRet);
    }
    return 0;
}