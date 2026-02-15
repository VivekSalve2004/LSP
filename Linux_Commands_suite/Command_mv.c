#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

// ./mvx 		SourcePath.txt 	DestPath.txt
//	argv[0] 	argv[1]			argv[2]
// argc = 3

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Error : Insufficient Arguments\n");
		printf("Usage : %s <Source Path> <Destination Path> \n" , argv[0]);
		return -1;
	}

	if(rename(argv[1] , argv[2]) == -1)
	{
		printf("Error : Unable to move \n");
		return -1;
	}
	
	return 0;
}
