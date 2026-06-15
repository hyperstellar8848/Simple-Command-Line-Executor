CC = gcc
CFLAGS = -Wall -g

all: cmd_executor

cmd_executor: cmd_executor.c
	$(CC) $(CFLAGS) cmd_executor.c -o cmd_executor

clean:
	rm -f cmd_executor
