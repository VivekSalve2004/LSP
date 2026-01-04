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



*/