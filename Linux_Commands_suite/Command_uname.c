#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

#define SIZE 1024

// ./unamex		
//  argv[0] 			
//  argc = 1

/*
	call the system call uname
	Print the information from utsname structure
*/

int main(int argc, char *argv[])
{
	struct utsname obj;
	int iRet = 0;
	iRet = uname(&obj);
	if(iRet == -1)
	{
		printf("Error : Unable to fetch system information \n");
		return -1;
	}
	printf("Operating System name : %s \n" , obj.sysname);
	printf("Node name : %s \n" , obj.nodename);
	printf("Operating System version no : %s \n" , obj.release);

	return 0;
}
