#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>
#include<dirent.h>
#include<ctype.h>

// ./unamex		
//  argv[0] 			
//  argc = 1

/*
	open directory /proc
	open all subdirectories whose name is integer 
	Inside that directory open comm
	Display name inside that file
*/

int is_all_digits(const char *s)
{
    if (*s == '\0') return 0;       // empty string → no
    while (*s)
    {
        if (!isdigit((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

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
        if (is_all_digits(entry->d_name)) 
		{
            char path[1024];
            char comm[1024];
            
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
