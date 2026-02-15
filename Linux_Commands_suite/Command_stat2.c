#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>

// ./statx		FileName
//	argv[0] 	argv[1]		
// argc = 2

/*
	Accept FileName from Command Line
	call access to check existence of file
	call stat system call to get files meta data
	Display the metadata
	
*/
void DisplayPermission(mode_t m)
{
	char Arr[11] = "-----------";

	if(S_ISDIR(m))       Arr[0] = 'd';
	if(S_ISLNK(m))       Arr[0] = 'l';

	// Regulat File permissions
	// Owner
	if(m & S_IRUSR)		Arr[1] = 'r';
	if(m & S_IWUSR)		Arr[2] = 'w';
	if(m & S_IXUSR)		Arr[3] = 'x';

	// Group
	if(m & S_IRGRP)		Arr[4] = 'r';
	if(m & S_IWGRP)		Arr[5] = 'w';
	if(m & S_IXGRP)		Arr[6] = 'x';

	// Others
	if(m & S_IROTH)		Arr[7] = 'r';
	if(m & S_IWOTH)		Arr[8] = 'w';
	if(m & S_IXOTH)		Arr[9] = 'x';

	Arr[10] = '\0';

	printf("File Permissions : %s \n ",Arr);
}

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
		struct stat sobj;
		int iRet = stat(argv[1] , &sobj);

		if(iRet == -1)
		{
			printf("Error : Unable to fetch statistical information \n");
			return -1;
		}

		printf("Name of File is : %s \n",argv[1]);
		printf("File size is : %ld \n",(long)sobj.st_size);
		printf("Inode number is : %ld \n",(long)sobj.st_ino);
		DisplayPermission(sobj.st_mode);
	}
	else
	{
		printf("Error : File not found \n");
		return -1;
	}

	return 0;
}
