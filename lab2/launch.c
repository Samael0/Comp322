// A program that allows one to set in motion another program, while also report some basic information.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void forkProcess(int argc, char *argv[]){
    // Fork a child process

    pid_t pid;
    int pointerStatus;
    int exitStatus;
    pid = fork(); // Forking Process

    if(pid == 0){ // Checking the child
        execve(argv[1], argv + 1, NULL);
        _exit(0);
    }
    else if(pid > 0){
        fprintf(stderr, "%s: $$ = %d\n", argv[1], pid); // Prints PID of child
        waitpid(pid, &pointerStatus,0);

        exitStatus = WEXITSTATUS(pointerStatus);

        fprintf(stderr, "%s: $? = %d \n", argv[1], exitStatus); // Prints return value of child
        exit(0);

    }

}

int main(int argc, char *argv[]){
    forkProcess(argc, argv);
    return 0;

}