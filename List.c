
/*
all are wrapper functions 
direct system call access is not given to user

File Subsystem
    open()
    close()
    creat()
    unlink()
    remove()
    read()
    write()
    pread()     positional
    pwrite()
    lseek()
    truncate()
    ftruncate()
    rename()
    link()
    symlink()
    readlink()
    sync()
    fsync()
    fdatasync()
    stat()
    fstat()
    lstat()

    opendir()
    closedir()
    readdir()
    chdir()
    mkdir()
    rmdir()
    getcwd()
    access()
    dup()
    dup2()

 
Memory Management
    brk()           break for both malloc free
    sbrk()
    memset()
    memcmp()
    memcpy()
    malloc()
    calloc()
    realloc()
    free()
    mmap()
    munmap()

Process Subsystem
    fork()
    exec()
    execl()
    getpid()
    getppid()
*    wait()          -> achives synchronizationn by parents execution till death of any first child
    waitpid()
    sleep()
    exit()
    _exit()
    atexit()
    nice()
    getpriority()
    setpriority()

    mkfifo()
    pipe()
    shmget()
    shmat()
    shmdt()
    msgget()
    msgsnd()
    msgrcv()
    signal()
    kill()



UREA
UFDT
File Table , IIT
Process table 
pprt - per process region table
region table    

argv[0] = myexe

program - static set of instructions

parent child relationship only in os for process 

region
virtual address space
physical address space

os commit 4 gb irrespective of ram to each process  -> virtual
kernel -> 100 mb    
text segement -> code segment -> static binary instructions

data region -> global variables -> dynamic memory

text region not expandable  -> fixed sized region

hdd -> text , data regions (no stack region)
ram -> all text,data,stack regions

so file -> shared object -> linux
dll -> windows
dilib -> macos

HDD -> inodes 13 member array
RAM -> page table

every region have their own page tables
page tables are in a table called region table
per process region table(pprt)
process table


Algorithms
1. allocreg()
2. freereg()
3. attach
4. detach
5. dupreg   -> fork()  , text,data,stack
6. growreg  -> brk() , sbrk()

memory allocation policies
1. Demand Paging
2. Swap partition 


process 0 -> swapper process
process 1 -> init process


before main function in c -> c runtime start up code

exec -> full blown process

waitall() -> parents waits till all its child die

orphan process -> when child process original creator parent dies child process becomes orphan

daemon process -> invisible not understandable , working in background for some time , runs in background without using any terminal utility

java -> garbage collector -> daemon process

TTY -> Tele Typed Terminal ,  Only stdin , stdout

bin -> apllication software
sbin -> (system binary) os software 

Zombie -> not currently running process , 

Linux -> priority value -> nice value
priority range -> (-20) - (19)              (40 values)
priority -> process table , UAREA
kernel limits nice value  from -19 to 20 (if 27 it is converted to 20) 

sudo -> super user do (user understands kernel)



Process Address Space

1.      Command Line Arguments
2.      Stack
3.      Potential Gap
4.      Data
5.      Text


malloc() -> return base address of allocated memory
brk()    -> return address after allocation or end of memory allocated

pointer arithematic not allowed for void * type


process pid  -> used for communication with os & other process

o.s. boooting -> real mode
after some time after booting it gets shifted to protected mode

real mode -> only process running
protected mode -> multiple process running

mode changes behaviour of os

real mode -> weak state
protected mode -> strong state

process scheduler -> schedules process at proper time

(Mode switch)
start -> real mode      -> protected mode       -> real mode -> end
        (single process)   (multiple processes)



Address bus(64 bit  , 2^64) capacity matters not ram capacity

dont call me i will call you    -> real mode , os observes the single process

call me when you need me  -> system call


process communication between process of diffrent machines is only posible by socket 

* IPC can be performed by 
    
1. named pipe       (frequently used)   (created on ram gets directory entry stored on HDD)
2. unnamed pipe     (temporarily used) (only on ram)        (both named & unnamed pipe stored data is wiped or cleaned after some time)
3. shared memory        -> kernel not totally involved (1 page (shared memory) common btw two process)
4. message queue        -> kernel involved
5. signals
6. socket

1 to 6 -> same pc
6 (socket) -> different pc

max pipe size -> 10 kb

duplex pipe -> both ends used for sendind & receiving data 
once data is read from pipe , pipe becomes empty


creator of shared memory and first writer to shared memory is -> server
first reader of shared memory -> client

unnamed pipe can be deleted when process which uses it is terminated


PIPE System calls -

1. mkfifo() -> create named pipe (special file) (10 kb) (any process can communicate)
2. mknode() -> create node
3. pipe()   -> unnamed pipe (10 kb) (only related process(parent child) can communicate)

Shared Memory system calls - (fastest memory , not going to kernel)

4. shmget() ->   
5. shmat()  ->
6. shmdt()  -> 

Message Queue system calls - (using kernel)

7. msgget()
8. msgsnd()
9. msgrcv()


signal -> no actual data is passed but an indicator 

Signal system calls -   (kernel involved)

10. signal()    -> inbuilt signals , user defined signals
11. kill()      


Randomization is not allowed in pipes -> random access to pipe(lseek not allowed)

in HDD space is given to pipe device , size -> 256 pipes only in unix

only name of named pipe is preserved its data is lost

in case of pipe -> blocking I/O
in case of regular file -> non-blocking I/O


ls | wc -l

./writer | ./reader

$ gcc pipewriter.c -o writer
$ ./writer
Jay Ganesh...
$ gcc pipereader.c -o reader
$ ./reader
Pune
Data received : Pune
$ ./writer | ./reader
Data received : Jay Ganesh...

$ ./myexe
PID is : 19468

$ kill -SIGINT 19468


Multitasking - 

1. Multiprocessing
2. Multitasking

only fork -> lightweight process (Thread)
both fork & exec -> process 

linker -> libc obj + pthread obj

void does not perform pointer arithematic 


gcc demo.c -pthread
gcc demo.c -lpthread

I/O bound -> multithreading
CPU Extensive -> multiprocessing

gcc -fPIC -shared -o libclient_1.so client_1.c

gcc server_1.c -o server_1 -ldl

// gcc -c client_1.c -o client_1.o
// ar rcs libclient_1.a client_1.o

ar  - archiac utility
rcs - replace create symbol index

You can check for them using:
ipcs -m (for shared memory)
ipcs -q (for message queues)

And remove them with:
ipcrm -m <shmid>

ROOT -> '/' -> inode no -> 1
fsck
vieditor


makefile only on linux distros
makefile -> build Automation

smart approach of makefile -> builds only changed files

target : dependency
    recipe

GPL -> GNU Public License    
    
every device driver is a kernel module


Kernel extensions 
Device Driver


Kernel Diary -> sudo dmesg
lsmod -> all active device drivers fed to kernel module for working

uname -r
FTP Server Project - 
ioctl lock



linux command suite - 






hexdump

pe (Portable executable) file format -> windows

4D 5A

hexdump ./cpx -b

/proc -> ps

find . -name  "*.c"



Kernel module

sudo insmod KernelModule_1.ko

lsmod   -> name , size

dmesg   -> output of kernel module can be seen

sudo rmmod KernelModule_1

modprob

modinfo Hello.ko > modinfo.txt

Imp questions -> Device file vs Device Driver

major number -> driver

minor nummber -> device

mknod -> device file

/dev -> all device files

Device file -> major no + minor no
               (Driver)   (Device)

               
$ mknod c /dev/tmp 551 11
        |
        b

$ ls -l /dev

$ stat /dev/tmp

sudo chmod 666 /dev/marvellous_driver 
sudo echo "Jay Ganesh..." > /dev/marvellous_driver

*/
