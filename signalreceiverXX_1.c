#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void MarvellousHandler(int no)
{
    printf("Marvellous Message - Signal arrived : %d\n",no);
    signal(SIGUSR1 , MarvellousHandler);
}

// void MarvellousHandler(int no)
// {

// }

int main()
{
    printf("PID is : %d\n",getpid());

    signal(SIGUSR1 , MarvellousHandler);

    while(1)
    {
        sleep(1);
    }

    

    return 0;
}