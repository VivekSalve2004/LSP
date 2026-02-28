// ./myexe
// ./myexe /home/Demo
// ./myexe /home/Demo 5

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

static volatile sig_atomic_t stop_flag = 0;

// ctrl+c handler
static void sigint_handler(int sig)
{
    (void)sig;                              // unused variable sig

    printf("Marvellous System Logger is terminating... \n");

    // Tell the threads to stop the execution 
    stop_flag = 1;

}

// Structure which holds all system information
typedef struct 
{
    double cpu;     // CPU Usage percentage
    double mem;     // RAM Usage percentage
    double disk;    // Harddisk Usage Percentage

}Snapshot;

// Global object which holds information
static Snapshot snap;

// Mutex Lock for critical section
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// Default Path for Disk
static const char * disk_path = "/";

// Sleep timer for log
static int interval_sec = 2;




int main(int argc , char * argv[])
{
    if(argc == 2)
    {
        disk_path = argv[1];
    }
    else if(argc == 3)
    {
        disk_path = argv[1];
        interval_sec = atoi(argv[2]);
    }

    printf("Marvellous System Logger \n");

    printf("Path is : %s \n",disk_path);
    printf("Interval is : %d\n",interval_sec);

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