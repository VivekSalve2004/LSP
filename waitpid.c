#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t childpid = 0;
    pid_t ret = 0;

    int status = 0;

    childpid = fork();

    if(childpid == 0)
    {
        printf("Child is running with PID : %d\n",getpid());
        sleep(10);
        printf("Child process exiting\n");
        exit(11);
    }
    else
    {
        printf("Parent is running \n");
        printf("Parent is waiting for child : %d",childpid);

        // waitpid(-1 , &status , 0);    first child death
        ret = waitpid(childpid , &status , 0);    // specified pid child death

        if(WIFEXITED(status))
        {
            printf("Child exited with PID : %d \n",ret);
            printf("Exit status of child is : %d\n",WEXITSTATUS(status));
        }
        
    }

    return 0;
}