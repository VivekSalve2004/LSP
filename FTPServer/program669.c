// Server Code
#include<stdio.h>               // printf , scanf
#include<stdlib.h>              // malloc , free
#include<string.h>              // memset , memcmp

#include<unistd.h>              //  close , write , read , (Macros)
#include<fcntl.h>               //  create , unlink

#include<sys/socket.h>          // socket , bind , listen , accept , connect
#include<netinet/in.h>          // sockaddr_in , htons

/*
struct sockaddr 
{
    sa_family_t sa_family;
    char        sa_data[14];
}
*/

int main()
{
    int ServerSocket = 0;
    int iRet = 0;
    int port = 11000;
    int ClientSocketFD = 0;

    struct sockaddr_in ServerAddr;

    // Step 1 : Create TCP Socket
    ServerSocket = socket(AF_INET , SOCK_STREAM , 0);
                        // IPv4     TCP          Default addr
    if(ServerSocket < 0)
    {
        printf("Unable to create Socket \n");
        return -1;
    }

    printf("Socket gets created successfully fd : %d\n",ServerSocket);
    
    // Step 2 : Attach the socket to IP Address & Port No

    // set memory with zero
    memset(&ServerAddr , 0 , sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port = htons(port);

    iRet = bind(ServerSocket , (struct sockaddr*) &ServerAddr , sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Bind System call Failed...\n");
        close(ServerSocket);
        return -1;
    }

    printf("Bind operation with socket is successfull \n");

    // step 3 : Mark the socket as active socket 

    iRet = listen(ServerSocket , 11);

    if(iRet == -1)
    {
        printf("Unable to convert socket in listen mode \n");
        return -1;
    }

    printf("Server is live at port : %d \n", port);

    // Step 4 : Accept new Socket request from client

    ClientSocketFD = accept(ServerSocket , NULL , NULL);

    if(ClientSocketFD == -1)
    {
        printf("Unable to accept request from client \n");
        return -1;
    }

    printf("Request accepted by server \n");

    return 0;
}