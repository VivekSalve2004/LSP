#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>

#define MAX_BUFFER_SIZE 1024

// ./lsx 	
//	argv[0] 
// argc = 1

/*
	Open the current directory(".")
	read all entries from that directory
	print the names of files
	close the directory
*/

int main(int argc, char *argv[])
{
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
		printf("%s\n",dobj->d_name);
	}

	closedir(dp);

	return 0;
}
