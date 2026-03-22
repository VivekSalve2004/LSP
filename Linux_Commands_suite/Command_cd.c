/*
 * ============================================================
 *  NOTE: Fundamental Limitation of cdx
 * ============================================================
 *
 *  This program CANNOT change the shell's working directory.
 *
 *  When you run ./cdx, the shell forks a child process:
 *
 *      Shell (PID 1001)  ← stays in original directory
 *          └── ./cdx (PID 1002)  ← chdir() only affects THIS
 *
 *  chdir() changes the working directory of the calling process
 *  only. Once cdx exits, the shell is completely unaffected.
 *
 *  This is why the real `cd` is a SHELL BUILTIN — it must run
 *  inside the shell process itself, not as a child process.
 *
 *  To truly change the shell's directory, cd must be executed
 *  by the shell directly, not by spawning a separate process.
 * ============================================================
 */

#include<stdio.h>
#include<unistd.h>

#define SIZE 1024

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
		printf("Usage : %s <~/DirectoryPath> \n" , argv[0]);
		return -1;
	}

	if(chdir(argv[1]) == -1)
	{
		perror(argv[1]);
		printf("Usage : %s <~/DirectoryPath> \n" , argv[0]);
		return -1;
	}

	char Buffer[SIZE];
	if (getcwd(Buffer, SIZE - 1) == NULL)
	{
		perror("getcwd");
		return -1;
	}
	printf("Current Directory changed to : %s \n",Buffer);

	return 0;
}
