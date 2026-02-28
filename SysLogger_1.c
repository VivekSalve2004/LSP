#define _GNU_SOURCE

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/statvfs.h>

// ctrl+c handler
static void sigint_handler(int sig)
{
    printf("ctrl+c arrived \n");

}

int main(int argc , char * argv[])
{
    printf("Marvellous System Logger \n");

    // Structure for handling ctrl+c
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));

    sa.sa_handler = sigint_handler;

    sigaction(SIGINT , &sa , NULL);

    while(1)
    {
        sleep(1);
    }

    

    return 0;
}