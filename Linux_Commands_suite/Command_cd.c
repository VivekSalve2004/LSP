#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SIZE 256

// ./cdx		DirectoryPath
//	argv[0] 	argv[1]		
// argc = 2

/*
	Accept new DirectoryPath from Command Line
	call chdir with that path
	call getcwd to check the changed 

*/

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Error : Insufficient Arguments\n");
		printf("Usage : %s <DirectoryPath> \n" , argv[0]);
		return -1;
	}

	if(chdir(argv[1]) == -1)
	{
		printf("Error : Unable to check current directory \n");
		return -1;
	}

	char Buffer[SIZE];
	memset(Buffer , '\0' , sizeof(Buffer));
	getcwd(Buffer , SIZE - 1);
	printf("Current Directory changed to : %s \n",Buffer);

	return 0;
}
