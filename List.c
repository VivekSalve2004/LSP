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
    wait()
    sleep()
    exit()
    _exit()



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



*/