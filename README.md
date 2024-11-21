## Repo for Lab Week 10
Complete assignment as assigned.

Note, no make file is provided.  It is suggested you create one to be more efficient building your programs.
#### What is a signal disposition?
A signal disposition defines how a process responds when it receives a specific signal. It's a per-process attribute; in a multithreaded application, the disposition of a particular signal is the same for all threads. For each signal, a process can pick one of the dispositions:
- Default Action: the action predefined by the system for that signal.
- Ignore the Signal: the process disregards the signal.
- Catch the Signal: the process specifies a custom handler function to execute upon receiving the signal.

#### What is a signal handler? What is it used for?
A signal handler is a user-defined function that a process executes in response to a specific signal. By catching signals, processes can perform custom actions, such as cleaning up resources or logging information before termination

#### Name and describe each of the five default dispositions.
Term: Terminates the process.
Ign: Ignores the signal.
Core: Terminates the process and generates a core dump.
Stop: Stops the process.
Cont: Continues a stopped process


#### Name and describe one way to programmatically send a signal to a process. Be able to give an example (the code) to send a signal.
One way to programmatically send a signal to a process is to use the kill system call kill(pid, SIGINT). Example - sending SIGINT to a process with PID 1111: kill(1111, SIGINT);

#### Name and describe one way to send a signal to a process from the command line. Be able to give an example (the command, key combination, etc.) to send a signal
The command - sending SIGTERM to a process with the PID 2222: kill -TERM 2222
Key combination - sending SIGINT: Ctrl+c

#### POSIX signal types:
- SIGINT: Interrupt from the keyboard. Default: Terminates the process. Does override to handle clean interruptions.
- SIGTERM: Termination request. Default: Terminates the process. Does override to allow graceful shutdown.
- SIGUSR1: User-defined signal. Default: Terminates the process. Does override for custom behaviors.
- SIGKILL: Forceful process termination. Default: Terminates the process. Does not override to ensure termination.
- SIGSTOP:Stops the process. Default: Stops the process. Does not override to ensure stoppage.