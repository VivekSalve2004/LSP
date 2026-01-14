# Linux System Programming (LSP) 🐧

This repository contains a comprehensive collection of low-level C programs designed to explore and demonstrate the core concepts of the **Linux Kernel API**, **Process Management**, and **File I/O operations**. 

The project serves as a technical portfolio of my expertise in Unix internals and systems-level software development.

---

## 🚀 Key Features & Implementation

### 📁 Advanced File Systems & I/O
* **System Calls:** Implementation of fundamental I/O using `open`, `read`, `write`, `creat`, and `close`.
* **Atomic Operations:** Demonstrations of `pread` and `pwrite` for thread-safe/position-independent file access.
* **Random Access:** Efficient file navigation using `lseek` to manipulate file offsets.
* **Descriptor Management:** Deep dive into file descriptor duplication using `dup` and `dup2`.
* **Memory Mapping:** High-performance file access via `mmap` and `munmap`.

### ⚡ Process Management & Control
* **Lifecycle:** Detailed examples of process creation (`fork`), execution (`exec` family), and termination (`exit`, `_exit`, `_Exit`).
* **Special States:** Hands-on implementation of **Zombie** and **Orphan** process scenarios to understand kernel process tracking.
* **Priority & Scheduling:** Managing process "niceness" and priority using `nice`, `getpriority`, and `setpriority`.
* **Resource Tracking:** Retrieving process metadata using `getpid`, `getppid`, and custom process naming via `prctl`.

### 🔗 Inter-Process Communication (IPC)
* **Named Pipes (FIFOs):** Implementation of Client-Server architecture using `mkfifo` for bidirectional communication between unrelated processes.

### 🛠 System Utilities & Error Handling
* **Error Management:** Robust implementation of `errno`, `perror`, and `strerror` to handle system-level failures.
* **Directory Operations:** Manual directory traversal and manipulation using `opendir`, `mkdir`, and `chdir`.
* **Cleanup:** Using `atexit` handlers to ensure graceful resource deallocation.

---

## 🛠 Tech Stack
* **Language:** C (100%)
* **Platform:** Linux / Unix-like Systems
* **Tools:** GCC, GDB, Make, Linux Man Pages (Section 2 & 3)

---

## 📂 Repository Structure

| File/Directory | Description |
| :--- | :--- |
| `open_*.c`, `read_*.c` | Deep dive into File I/O system calls. |
| `pid_*.c`, `fork_*.c` | Process identification and creation logic. |
| `namedpipe*.c` | Client-Server IPC implementation. |
| `lseek_*.c` | File offset manipulation and sparse file handling. |
| `brk_*.c` | Low-level memory management and heap segment control. |
| `Data/` | Test datasets used for I/O operations. |

---

## 👨‍💻 For Recruiters: Why this Matters
This repository demonstrates a strong foundation in **Systems Programming**, which is critical for roles in:
1.  **Embedded Systems:** Understanding kernel-space/user-space boundaries.
2.  **Backend Engineering:** Writing high-performance, resource-efficient code.
3.  **Cybersecurity:** Understanding process isolation and system-level vulnerabilities.
4.  **Performance Engineering:** Utilizing memory mapping and asynchronous I/O for speed.

---

## 📥 Getting Started

### Prerequisites
* A Linux environment (Ubuntu/Fedora/Debian recommended).
* Standard Build Tools: `sudo apt install build-essential`

### Compilation & Execution
```bash
# Clone the repository
git clone [https://github.com/VivekSalve2004/LSP.git](https://github.com/VivekSalve2004/LSP.git)

# Navigate to the folder
cd LSP

# Compile a specific file (e.g., process creation)
gcc fork_1.c -o myfork

# Run the executable
./myfork


---
**Contact:** [viveksalve04@gmail.com](mailto:viveksalve04@gmail.com) | [LinkedIn](https://www.linkedin.com/in/vivek-salve-1b6364287/) 
**Status:** Active Learning & Development
