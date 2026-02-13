// Server Application
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<fcntl.h>

#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Commandline Application
//  1 st Argument : Port Number
//  ./server    9000
//  argv[0]     argv[1]
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc , char *argv[])
{
    int ServerSocket = 0;
    int ClientSocket = 0;
    int port = 0;
    int iRet = 0;

    pid_t pid = 0;

    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;

    socklen_t AddrLen = sizeof(ClientAddr);

    if((argc < 2) || (argc > 2))
    {
        printf("Unable to proceed as Invalid no of arguments \n");
        printf("please provide the port no\n");
        return -1;
    }

    // Port No of server
    port = atoi(argv[1]);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //  step 1 : create TCP Socket 
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    ServerSocket = socket(AF_INET , SOCK_STREAM , 0);

    if(ServerSocket < 0)
    {
        printf("Unable to create server socket \n");
        return -1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  step 2 : Bind socket to ip & port 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    memset(&ServerAddr,0,sizeof(ServerAddr));

    // Initialize structure
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    iRet = bind(ServerSocket , (struct sockaddr * ) &ServerAddr , sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to bind \n");
        close(ServerSocket);
        return -1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  step 3 : Listen for client connections
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    iRet = listen(ServerSocket , 11);

    if(iRet == -1)
    {
        printf("Server unable to listen request \n");
        close(ServerSocket);
        return -1;
    }

    printf("Server is running on port : %d\n",port);


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  Loop which accepts client request continuosly
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Loop to accept multiple client requests
    while(1)
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //  step 4 : Accept the client request
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        memset(&ClientAddr,0,sizeof(ClientAddr));

        printf("Server is waiting for client request \n");
        ClientSocket = accept(ServerSocket , (struct sockaddr * ) &ClientAddr , &AddrLen);

        if(ClientSocket < 0)
        {
            printf("Unable to accept client request \n");

            continue;   // Used for while
        }

        printf("Client gets connected : %s \n",inet_ntoa(ClientAddr.sin_addr));

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //  step 5 : Create new process to handle client request
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        pid = fork();

        if(pid < 0)
        {
            printf("Unable to create new process for client request \n");
            close(ClientSocket);
            continue;
        }

        // New process gets created for client 
        if(pid == 0)
        {
            printf("New process is created for client request \n");
            close(ServerSocket);
            
        }

    }   // End of while

    return 0;
}   // End of main