<div align="center">
 
# 🐧 Linux System Programming (LSP)
 
[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Unix-orange?style=for-the-badge&logo=linux)](https://www.linux.org/)
[![Tools](https://img.shields.io/badge/Tools-GCC%20%7C%20GDB%20%7C%20Make-green?style=for-the-badge)](https://gcc.gnu.org/)
[![Status](https://img.shields.io/badge/Status-Active%20Development-brightgreen?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)
 
### *A hands-on deep dive into the Linux Kernel API — from file descriptors to kernel modules.*
 
[📖 Explore Code](#-repository-structure) • [🚀 Quick Start](#-getting-started) • [💼 For Recruiters](#-for-recruiters) • [📬 Contact](#-contact)
 
</div>
 
---
 
## 🔍 Overview
 
This repository is a **comprehensive, practical portfolio** of low-level systems programming in C on Linux. It covers the full spectrum of the Linux Kernel API — from raw file I/O and process management to **kernel module development**, **device drivers**, **multithreading**, and **network programming**.
 
Every program is a focused, runnable demonstration of a specific system call or kernel concept, making this repo both a learning resource and a proof of real-world systems expertise.
 
---
 
## 🧠 What's Inside — Core Topics
 
### 📁 File I/O & Descriptor Management
| System Call | Programs | What It Demonstrates |
|---|---|---|
| `open`, `read`, `write`, `creat`, `close` | `creat_1.c`, `creat_2.c` | Fundamental POSIX file I/O |
| `lseek` | `lseek_1.c` → `lseek_4.c` | Random access, sparse files, offset control |
| `dup`, `dup2` | `dup_1.c` → `dup_3.c` | File descriptor aliasing and redirection |
| `ftruncate` | `ftruncate_1.c`, `ftruncate_2.c` | File size control |
| `link` | `link_1.c`, `link_2.c` | Hard links and inode management |
 
---
 
### ⚡ Process Management & Control
| Concept | Programs | What It Demonstrates |
|---|---|---|
| `fork` | `fork_1.c` → `fork_6.c` | Process creation, parent-child relationships |
| `exec` family | `exec_1.c` → `exec_4.c` | Process image replacement |
| `exit`, `_exit`, `_Exit` | `exit_1.c` → `exit_3.c`, `_exit_1.c`, `_Exit_1.c` | Termination semantics and cleanup |
| Zombie & Orphan | `fork_*.c` variants | Kernel process tracking edge cases |
| `nice`, `getpriority`, `setpriority` | `getpriority_1.c` → `getpriority_3.c` | CPU scheduling and niceness |
| `atexit` | `atexit_1.c`, `atexit_2.c` | Graceful resource cleanup handlers |
| `prctl`, `getpid`, `getppid` | Various | Process metadata and naming |
| `brk`, `sbrk` | `brk_1.c` → `brk_3.c` | Low-level heap/memory segment control |
 
---
 
### 🔗 Inter-Process Communication (IPC)
| Mechanism | Directory / File | What It Demonstrates |
|---|---|---|
| Named Pipes (FIFOs) | Root + `FTPServer/` | Client-Server communication between unrelated processes |
| FTP Server | `FTPServer/` | Full FTP-style IPC application using pipes |
| System V IPC key | `ftok_1.c` | Generating unique IPC keys |
 
---
 
### 🧵 Multithreading & Synchronization
| Concept | Programs | What It Demonstrates |
|---|---|---|
| POSIX Threads | `Multithreading_1.c` | Thread creation, joining, and lifecycle |
| Mutex Locking | `Mutex_1.c`, `Mutex_2.c` | Race condition prevention and critical sections |
| Multiprocessing | `Multiprocessing_1.c`, `Multiprocessing_2.c` | Parallel process execution patterns |
 
---
 
### 🔧 Libraries: Static & Dynamic Linking
| Type | Directory | What It Demonstrates |
|---|---|---|
| Static Library | `Static/` | Compile-time linking with `.a` archives |
| Dynamic/Shared Library | `Dynamic/` | Runtime linking with `.so` shared objects |
 
---
 
### 🏗️ Build System (Makefile Mastery)
| Demo | Directory | Concept |
|---|---|---|
| Basic Rules | `MakeFileDemo1/` | Targets, dependencies, recipes |
| Variables | `MakeFileDemo2/` | `CC`, `CFLAGS`, automatic variables |
| Pattern Rules | `MakeFileDemo3/` | `%.o: %.c` compilation patterns |
| Phony Targets | `MakeFileDemo4/` | `clean`, `all`, `.PHONY` |
| Multi-Module | `MakeFileDemo5/` | Real-world multi-file project build |
 
---
 
### 🖥️ Kernel Development
| Area | Directory | What It Demonstrates |
|---|---|---|
| Loadable Kernel Module | `KernelModule1/` | Writing, loading (`insmod`), and unloading (`rmmod`) LKMs |
| Device Drivers | `Device_Drivers/` | Character device driver development |
 
---
 
### 🛠️ System Utilities
| Category | Programs | What It Demonstrates |
|---|---|---|
| Error Handling | `error_1.c` → `error_6.c` | `errno`, `perror`, `strerror` robustly |
| System Logger | `SysLogger_1.c` → `SysLogger_5.c` | `syslog`, `openlog`, `closelog` — kernel log integration |
| Directory Ops | `chdir_1.c`, `fchdir_1.c`, `getcwd_1.c`, `getcwd_2.c` | Filesystem navigation |
| Command Line | `CommandLine.c` → `CommandLine_4.c` | `argc`/`argv` parsing patterns |
| Linux Commands | `Linux_Commands_suite/` | Custom reimplementations of `ls`, `ps`, `cat`, etc. |
| Debug | `debug_1.c` | GDB-compatible debug patterns |
| Process Project | `Process_Project/` | Complete multi-concept process management project |
 
---
 
## 📂 Repository Structure
 
```
LSP/
├── 📁 Device_Drivers/        # Character device driver implementation
├── 📁 Dynamic/               # Dynamic (.so) shared library demos
├── 📁 FTPServer/             # IPC-based FTP-style client-server app
├── 📁 KernelModule1/         # Loadable kernel module (LKM) development
├── 📁 Linux_Commands_suite/  # Custom Linux command reimplementations
├── 📁 MakeFileDemo1-5/       # Progressive Makefile concepts
├── 📁 Process_Project/       # Full process management project
├── 📁 Static/                # Static (.a) library demos
├── 📁 Data/                  # Test datasets for I/O operations
│
├── 🔵 brk_*.c               # Heap memory management
├── 🔵 fork_*.c, exec_*.c    # Process creation & execution
├── 🔵 exit_*.c, _exit_*.c   # Process termination semantics
├── 🔵 lseek_*.c             # File offset manipulation
├── 🔵 dup_*.c               # File descriptor duplication
├── 🔵 creat_*.c             # File creation syscalls
├── 🔵 error_*.c             # Error handling patterns
├── 🔵 Multithreading_*.c    # POSIX thread demos
├── 🔵 Mutex_*.c             # Thread synchronization
├── 🔵 SysLogger_*.c         # syslog integration
├── 🔵 getpriority_*.c       # Process scheduling
├── 🔵 CommandLine_*.c       # CLI argument handling
└── 📄 Makefile              # Root build configuration
```
 
---
 
## 💼 For Recruiters
 
> **Why this repo signals strong engineering fundamentals:**
 
This is not tutorial code — it's **deliberate, structured exploration** of the Linux kernel interface. Here's why it matters for key roles:
 
| Role | Relevant Skills Demonstrated |
|---|---|
| **Embedded / Systems Engineer** | Device drivers, kernel modules, `brk`/`sbrk`, process isolation |
| **Backend / Infrastructure Engineer** | IPC (FIFOs, FTP server), multithreading, mutex, high-perf I/O |
| **Cybersecurity Engineer** | Process isolation, descriptor management, zombie/orphan handling |
| **Performance Engineer** | `mmap`, `lseek`, atomic `pread`/`pwrite`, memory-mapped I/O |
| **Kernel / OS Developer** | LKM development, device drivers, `dmesg` logging, `syslog` |
 
**Depth indicators:**
- ✅ 47+ commits showing active, iterative development
- ✅ Kernel-space programming (modules + drivers) — rare at student level
- ✅ Build system mastery (5 progressive Makefile demos)
- ✅ Full static + dynamic library lifecycle
- ✅ Working FTP-style networked IPC application
 
---
 
## 🚀 Getting Started
 
### Prerequisites
 
```bash
# Linux environment (Ubuntu/Debian recommended)
sudo apt update
sudo apt install build-essential gcc gdb make linux-headers-$(uname -r)
```
 
### Clone & Compile
 
```bash
# Clone the repository
git clone https://github.com/VivekSalve2004/LSP.git
cd LSP
 
# Compile any individual file
gcc fork_1.c -o fork_demo && ./fork_demo
 
# Compile with threading
gcc Multithreading_1.c -o thread_demo -lpthread && ./thread_demo
 
# Use the root Makefile
make
 
# Build a specific Makefile demo
cd MakeFileDemo3 && make
```
 
### Load the Kernel Module (requires root)
 
```bash
cd KernelModule1
make
sudo insmod <module_name>.ko
dmesg | tail        # View kernel log output
sudo rmmod <module_name>
```
 
---
 
## 🗺️ Learning Path
 
If you're exploring this repo to learn, follow this order:
 
```
1. error_*.c          → Understand error handling first
2. creat_*.c, lseek_* → File I/O fundamentals
3. fork_*.c, exec_*   → Process management
4. Multithreading_*   → Threads + Mutex
5. MakeFileDemo1-5/   → Build systems
6. Static/, Dynamic/  → Libraries
7. FTPServer/         → Real IPC application
8. KernelModule1/     → Kernel space 🎯
9. Device_Drivers/    → Driver development 🔥
```
 
---
 
## 📬 Contact
 
<div align="center">
 
**Vivek Salve**
 
[![Email](https://img.shields.io/badge/Email-viveksalve04%40gmail.com-red?style=for-the-badge&logo=gmail)](mailto:viveksalve04@gmail.com)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Vivek%20Salve-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/vivek-salve-1b6364287/)
[![GitHub](https://img.shields.io/badge/GitHub-VivekSalve2004-black?style=for-the-badge&logo=github)](https://github.com/VivekSalve2004)
 
*Open to roles in Systems Programming, Embedded Development, Backend Engineering, and Kernel Development.*
 
</div>
 
---
 
<div align="center">
 
⭐ **If this repo helped you learn, consider starring it!** ⭐
 
*Active Learning & Development — updated regularly*
 
</div>
