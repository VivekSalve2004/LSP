#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define DEVICE_PATH "/dev/marvellous_driver"
#define BUFFER_SIZE 1024

int main()
{
    int fd = 0 , iRet = 0;
    char read_buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];

    printf("Openeing the Marvellous Device...\n");

    // cat /dev/marvellous_driver
    fd = open(DEVICE_PATH , O_RDWR) ;

    if(fd < 0)
    {
        printf("Error : Unable to open marvellous device \n");
        return -1;
    }

    printf("Marvellous Device opened successfully \n");

    printf("Enter the data for marvellous driver \n");

    fgets(write_buffer , BUFFER_SIZE , stdin);

    write_buffer[strcspn(write_buffer , "\n" )] = 0;

    printf("Writing to Marvellous Device \n");

    // echo "Jay Ganesh..." > /dev/marvellous_driver
    iRet = write(fd , write_buffer , strlen(write_buffer));
    
    if(iRet < 0)
    {
        printf("Error : Unable to write into Marvellous Device \n");
        close(fd);
        return -1;
    }

    printf("Data successfully written into Marvellous Driver \n");

    printf("Reading the data from Marvellous Driver \n");

    // cat /dev/marvellous_driver
    iRet = read(fd , read_buffer , BUFFER_SIZE);

    if(iRet < 0)
    {
        printf("Error : Unable to read from Marvellous Driver \n");
        close(fd);
        return -1;
    }

    read_buffer[iRet] = '\0';

    printf("Data Received from Marvellous Driver : %s\n",read_buffer);

    printf("Closing Marvellous Driver...\n");

    close(fd);

    return 0;
}