# Compiler flags and settings
CFLAGS=-c -g -Wall -Werror
CC=gcc

# List of executables to generate
EXECUTABLES=recv_signal send_signal signal_alarm signal_handler signal_segfault signal_sigaction

# Rule to build all executables
all: $(EXECUTABLES)

# Rule for each executable
recv_signal: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

send_signal: send_signal.o
	$(CC) -o send_signal send_signal.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_segfault: signal_segfault.o
	$(CC) -o signal_segfault signal_segfault.o

signal_sigaction: signal_sigaction.o
	$(CC) -o signal_sigaction signal_sigaction.o

# Rule to clean up generated files
clean:
	rm -f *.o $(EXECUTABLES)

# Pattern rule for compiling .o files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<
