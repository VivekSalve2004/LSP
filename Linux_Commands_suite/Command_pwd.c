#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SIZE 1024

// ./pwdx		
//  argv[0] 			
//  argc = 1

/*
	call the system call getcwd
	Print the result of getcwd
*/

int main(int argc, char *argv[])
{
	char Buffer[SIZE];

	memset(Buffer , '\0' , SIZE);

	getcwd(Buffer , sizeof(Buffer));

	printf("%s \n",Buffer);

	return 0;
}
