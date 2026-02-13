// Client Application

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
//  1 st Argument : IP Address
//  2 st Argument : Port Number
//  3 st Argument : Targeted file name
//  4 st Argument : new file name
//
//  ./client    127.0.0.1   9000     demo.txt    a.txt
//  argv[0]     argv[1]     argv[2]  argv[3]    argv[4]
//
//  argc = 5
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc , char *argv[])
{
    int Sock = 0;
    struct sockaddr_in ServerAddr;

    char *ip = NULL;                // argv[1]
    char *Filename = NULL;          // argv[3]
    char *OutFilename = NULL;       // argv[4]

    int port = 0;                   // argv[2]

    if(argc < 5 || argc > 5)
    {
        printf("Unable to proceed as invalid no of arguments \n");
        printf("Please provide below arguments : \n");
        printf("1 st Argument : IP Address \n2 st Argument : Port Number \n3 st Argument : Targeted file name \n4 st Argument : new file name   \n");

        return -1;
    }

    // Store Command line arguments into variables
    ip = argv[1];
    port = atoi(argv[2]);
    Filename = argv[3];
    OutFilename = argv[4];

    /////////////////////////////////////////////////////
    //  Step 1 : Create TCP socket
    /////////////////////////////////////////////////////

    Sock = socket(AF_INET, SOCK_STREAM, 0);

    if(Sock < 0)
    {
        printf("Unable to create the client socket\n");
        return -1;
    }

    /////////////////////////////////////////////////////
    //  Step 2 : Connect with server
    /////////////////////////////////////////////////////
    
    memset(&ServerAddr,0,sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);

    // Convert the IP address into binary format
    inet_pton(AF_INET, ip, &ServerAddr.sin_addr);

    iRet = connect(Sock, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server\n");

        close(Sock);

        return -1;
    }

    // Sending file name to server
    write(Sock,Filename,strlen(Filename));
    
    return 0;
}   // End of main