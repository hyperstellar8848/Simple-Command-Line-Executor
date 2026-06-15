1. Project Description & Requirements:
This project implements a minimal Linux command-line shell running in an 
infinite execution loop. It displays a custom prompt 'cmd> ', parses raw 
user keyboard input into string vectors, and executes instructions. 
Built-in instructions (pwd, exit) run natively inside the master process 
to avoid performance overhead. External commands (e.g., ls, echo, whoami) 
are managed by spinning up isolated child environments via fork(), replacing 
the binary image with execvp(), and monitoring execution status using wait() 
to eliminate system zombie leakages.

2. Compilation Instructions:
To compile the source code cleanly into an executable format, run:
make

This maps dependencies through GCC with full diagnostic warning alerts (-Wall) 
and structural debugging data symbols (-g).

3. Execution Instructions:
Launch the standalone compiled shell binary via:
./cmd_executor

4. Verification & Testing Examples:

Example A (Built-in Location Tracking):
cmd> pwd
/home/ubuntu/os_lab

Example B (External Program Dispatch):
cmd> ls -l
total 24
-rw-r--r-- 1 ubuntu ubuntu  1725 Jun 15 22:00 cmd_executor.c
-rwxr-xr-x 1 ubuntu ubuntu 16304 Jun 15 22:01 cmd_executor
-rw-r--r-- 1 ubuntu ubuntu   148 Jun 15 22:00 Makefile

Example C (Graceful Missing-Command Exception Tracking):
cmd> blah
command not found: blah

To terminate the active interface loop safely and clean up memory:
cmd> exit
