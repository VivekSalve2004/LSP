#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void MarvellousHandler(int no)
{
    if(no == SIGUSR1)
    {
        printf("Marvellous Message - SIGUSR1 arrived : %d\n",no);
    }
    else if(no == SIGINT)
    {
        printf("Marvellous Message - SIGINT arrived : %d\n",no);
    }

}

int main()
{
    printf("PID is : %d\n",getpid());

    signal(SIGUSR1 , MarvellousHandler);
    signal(SIGINT , MarvellousHandler);

    while(1)
    {
        sleep(1);
    }

    

    return 0;
}