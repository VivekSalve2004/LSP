#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main()
{
    int ret = 0;

    ret = nice(0);
    
    printf("Current nice value : %d\n",ret);

    ret = nice(-5);             // Increase Priority

    if(ret == -1)
    {
        printf("%s\n",strerror(errno));
    }

    printf("Current nice value : %d\n",ret);

    return 0;
}