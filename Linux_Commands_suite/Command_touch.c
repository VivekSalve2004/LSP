#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

// ./touchx		FileName
//	argv[0] 	argv[1]		
// argc = 2

/*
	Accept FileName from Command Line
	Check whether file is existing or not
	if it exists return 
	if it does not exists
	Create that file
*/

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Error : Insufficient Arguments\n");
		printf("Usage : %s <FileName> \n" , argv[0]);

		return -1;
	}

	if(access(argv[1] , F_OK) == 0)
	{
		return 0;
	}
	else
	{
		creat(argv[1] , 0777);
	}

	return 0;
}
