# Lab 2

## Launch To-Do
* [] Forks a child process
* []Parent process prints the PID of the child on stderr 
* []The child process executes the supplied command
    * []child needs to prepare the new argv structure
* []Parent prints the return value of the child on stderr

## Tube To-Do
* []Program allocates a pipe
* []Program forks two children
* []The parent process prints the PID of both children on stderr
* []The parent process closes access to the pipe and the child processes wires the pipe to allow for inter-process communication
    * []via the standard stdout-stdin approach

## Update History
* Update 1
    * Created launch program that forks a child process and prints information using stderr. Not yet tested. Working on Tube program next

