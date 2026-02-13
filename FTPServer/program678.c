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


    return 0;
}