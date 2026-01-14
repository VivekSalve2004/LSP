# Define the compiler
CC = gcc

# Define compiler flags (optional but professional)
CFLAGS = -Wall -g

# The "all" target - what happens when you just type 'make'
all: open_1 fork_1 pipe_1

open_1: open_1.c
	$(CC) $(CFLAGS) open_1.c -o open_1

fork_1: fork_1.c
	$(CC) $(CFLAGS) fork_1.c -o fork_1

pipe_1: namedpipeserver.c
	$(CC) $(CFLAGS) namedpipeserver.c -o pipe_server

# A "clean" target to remove executables
clean:
	rm -f open_1 fork_1 pipe_server