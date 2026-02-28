// ./myexe
// ./myexe /home/Demo
// ./myexe /home/Demo 5

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Header File Inclusion
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Global variable creation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
static char * disk_path = "/";

// Sleep timer for log
static int interval_sec = 2;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Helper functions definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// Function to collect CPU Information 
///////////////////////////////////////////////////////////////////////////

static double cpu_percent()
{
    // Logic to fetch CPU Information 
    return 0.0;
}

///////////////////////////////////////////////////////////////////////////
// Function to collect Memory Information 
///////////////////////////////////////////////////////////////////////////

static double mem_percent()
{
    // Logic to fetch Memory Information 
    return 0.0;
}

///////////////////////////////////////////////////////////////////////////
// Function to collect Disk Information 
///////////////////////////////////////////////////////////////////////////

static double disk_percent(char *path)
{
    // Logic to fetch Disk Information 
    return 0.0;
}

// Thread proc for Thread which collects system information 
static void * collector_thread(void *arg)
{
    double c = 0.0 , m = 0.0 , d= 0.0;
    (void)arg;

    printf("Inside Collector thread \n");

    
    // Enter if ctrl+c is not arrived 
    while(!stop_flag)
    {
        // Calculate the current resource usage 

        c = cpu_percent();
        m = mem_percent();
        d = disk_percent(disk_path);

        // Start the critical section 

        pthread_mutex_lock(&mtx);

            snap.cpu = c;
            snap.mem = m;
            snap.disk = d;

        // End of critical section
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

// Thread proc for Thread which writes log 
static void * logger_thread(void *arg)
{
    double m = 0.0 , c = 0.0 , d = 0.0;
    (void)arg;

    printf("Inside Logger thread \n");

    int fd = 0;
    int i = 0;

    fd = open("Marvellous_log.txt" , O_CREAT | O_WRONLY | O_APPEND , 0666);

    char Welcome[] = "Marvellous System Logger";

    write(fd , Welcome, strlen(Welcome));

    while(!stop_flag)
    {
        pthread_mutex_lock(&mtx);

            d = snap.disk;
            c = snap.cpu;
            m = snap.mem;

        pthread_mutex_unlock(&mtx);
        // Write the information of structure snap into the file   
        // Prepare string using sprintf 
        char line[256];
        // Write that string into log file 

        // write(fd , line , strlen(line));

        // Sleep for interval 
        for(i=0;i<interval_sec && !stop_flag; i++)
        {
            sleep(1);
        }
    }

    close(fd);

    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Entry Point Function of project 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    // Thread to collect the information
    pthread_t t_collect;

    // Thread to write data into log
    pthread_t t_log;
    
    // create thread to collect information
    pthread_create(&t_collect,NULL,collector_thread,NULL);

    // create thread to write data into log 
    pthread_create(&t_log,NULL,logger_thread,NULL);

    // Main thread waiting for child threads 
    pthread_join(t_collect,NULL);
    pthread_join(t_log,NULL);

    printf("Marvellous System Logger terminating...\n");

    return 0;
}