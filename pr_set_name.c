// After running, ps aux | grep MyCustomProcess shows the new name 

// gcc pr_set_name.c -o myexe
// ./myexe & # Background it
// PID_CHECK=$!
// cat /proc/$PID_CHECK/comm # Shows: MyCustomProcess
// ps -p $PID_CHECK -o pid,comm # Shows: [pid] MyCustomProcess

#include<stdio.h>
#include<sys/prctl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    prctl(PR_SET_NAME, "MyCustomProcess", 0, 0, 0);
    printf("\n");
    printf("Process name set. Check with 'ps -eo pid,comm'\n");
    sleep(30);

    return 0;
}