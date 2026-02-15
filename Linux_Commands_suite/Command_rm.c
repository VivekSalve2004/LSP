#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

// ./rmx		FileName
//  argv[0] 	argv[1]		
//  argc = 2

/*
	call the system call uname
	Print the information from utsname structure
*/

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Error : Insufficient Arguments \n");
		printf("Usage : %s <Path> \n",argv[0]);
		return -1;
	}

	if(access(argv[1] , F_OK) == 0)
	{
		if(unlink(argv[1]) == -1)
		{
			printf("Error : File %s cannot be deleted \n",argv[1]);
			return -1;
		}

		printf("File : %s Deleted successfully \n",argv[1]);
	}
	else 
	{
		printf("Error : File does not exist \n");
		return -1;
	}

	return 0;
}
