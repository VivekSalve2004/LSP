#include<stdio.h>
#include<unistd.h>
#include<pwd.h>

int main()
{
    uid_t iRet = 0;;

    iRet = getuid();

    struct passwd *pw = getpwuid(iRet);

    if(pw)
    {
        printf("User : %s \n" , pw->pw_name);
        printf("Encrypted Password : %s \n" , pw->pw_passwd);
        printf("UID : %u \n" , pw->pw_uid);
        printf("GID : %u \n" , pw->pw_gid);
        printf("Real Name : %s \n" , pw->pw_gecos);
        printf("Home Directory Path : %s \n" , pw->pw_dir);
        printf("Users Default Shell : %s \n" , pw->pw_shell);
    }
    else
    {
        printf("Error : Could not find username for UID %u \n",iRet);
        return -1;
    }
    return 0;
}