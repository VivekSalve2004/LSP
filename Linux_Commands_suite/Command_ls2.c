#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>

#define MAX_BUFFER_SIZE 1024

// ./lsx		-i 	
//	argv[0] 	argv[1]

// argc = 2

/*
	Open the current directory(".")
	read all entries from that directory
	print the names of files
	close the directory
*/

int main(int argc, char *argv[])
{
	int option = 0;
	// 1 : ls -a
	// 2 : ls -i

	option = argc;

	if(argc == 1)
	{
		option = 1;
	}
	else if(strcmp(argv[1] , "-a") == 0)
	{
		option = 1;
	}
	else if(strcmp(argv[1] , "-i") == 0)
	{
		option = 2;
	}
	else
	{
		printf("Error : There is no such option\n");
		return -1;
	}

	char * path = ".";
	DIR * dp = NULL;	
	dp = opendir(path);

	if(dp == NULL)
	{
		printf("Error : Unable to open directory\n");
		return -1;
	}

	struct dirent * dobj;

	while((dobj = readdir(dp)) != NULL)
	{
		
		if(option == 1)
		{
			printf("%s\n",dobj->d_name);
		}
		if(option == 2)
		{
			printf("%ld\t%s\n",dobj->d_ino , dobj->d_name);
		}
	}

	closedir(dp);

	return 0;
}
