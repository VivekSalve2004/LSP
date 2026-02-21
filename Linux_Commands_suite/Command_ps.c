#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>
#include <dirent.h>
#include <ctype.h>

// ./unamex		
//  argv[0] 			
//  argc = 1

/*
	open directory /proc
	open all subdirectories whose name is integer 
	Inside that directory open comm
	Display name inside that file
*/

int main(int argc, char *argv[])
{
	struct dirent *entry;
    DIR *dp = opendir("/proc");

    if (dp == NULL) 
	{
        perror("Could not open /proc");
        return 1;
    }

    printf("%-10s %s\n", "PID", "COMMAND");
    printf("--------------------------\n");

    while ((entry = readdir(dp))) 
	{
        if (isdigit(entry->d_name[0])) 
		{
            char path[256];
            char comm[256];
            
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);

            int fd = open(path, O_RDONLY);
            if (fd != -1) 
			{
                ssize_t n = read(fd, comm, sizeof(comm) - 1);
                if (n > 0) 
				{
                    comm[n-1] = '\0'; // Remove trailing newline
                    printf("%-10s %s\n", entry->d_name, comm);
                }
                close(fd);
            }
        }
    }
	
    closedir(dp);
	
	return 0;
}
