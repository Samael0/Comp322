// A program that sets to programs into motion that are connected via a tube that transports 
// inter-process communication, while also report some basic information

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void forking(int argc, char *argv[], int argz){
    int pipeOne[2];
    int waitOne;
    int waitTwo;
    int stateOne; 
    int stateTwo;
    pid_t pid;
    pid_t pidTwo;

    pipe(pipeOne); // Allocate a pipe
    pid = fork(); // First fork

    waitOne = waitpid(pid, &stateOne, WUNTRACED);

    if(pid == -1){ // Error forking
        fprintf(stderr, "Fork Error... %d\n", errno);
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // This is the child
        dup2(pipeOne[1], 1);
        execve(argv[1], argv + 1, NULL);
        _exit(0);
    }
    else{
        pidTwo = fork(); // Second fork
        if(pidTwo == -1){
            fprintf(stderr, "Fork Error... %d\n", errno);
            exit(EXIT_FAILURE);
        }
        else if(pidTwo > 0){ // Printing PID of both child
            fprintf(stderr, "%s: $$ = %d\n", argv[1], pid);
            fprintf(stderr, "%s: $$ = %d\n", argv[argz], pidTwo);
            waitTwo = waitpid(pidTwo, &stateTwo, WUNTRACED);
        }
        else if(pidTwo == 0){ // Second child
            dup2(pipeOne[0], 0);
            execve(argv[argz], argv + argz, NULL);
            _exit(0);
        }
        if(pid > 0){
            int exitOne = WEXITSTATUS(stateOne);
            int exitTwo = WEXITSTATUS(stateTwo);

            fprintf(stderr, "%s: $? = %d\n", argv[1], exitOne);
            fprintf(stderr, "%s: $? = %d\n", argv[argz], exitTwo);

            close(pipeOne[1]); // Closing the pipe
            close(pipeOne[0]); // Cloising the pipe
        }
        exit(0);
    }

}

int main(int argc, char *argv[]){
    int argz;

    // Find the second argument
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i] , ",") == 0) {
            argv[i] = NULL;
            argz = i + 1;
        }
    }

    forking(argc, argv, argz);
    return 0;
}