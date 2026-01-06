// steps to run this code

/*

gcc setpriority_3.c -o myexe
sudo ./myexe
enter your password : 

*/

#include<stdio.h>
#include <sys/resource.h>
#include<stdlib.h>

int main()
{
    int iRet = 0;
    int which = PRIO_USER;
    id_t who = 0; 
    int new_priority = 5;

    iRet = setpriority(which,who,new_priority);
    if(iRet == -1)
    {
        perror("setpriority(PRIO_USER) failed");
        exit(1);   
    }
    else
    {
        printf("priority (PRIO_USER, caller UID) is %d\n",iRet);
    }
    return 0;
}