// A program that sets to programs into motion that are connected via a tube that transports 
// inter-process communication, while also report some basic information

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void forking(int argc, char *argv[], int argz){
    int pipeOne[2];
    int waitOne;
    int waitTwo;
    int stateOne; 
    int stateTwo;
    pid_t pid;
    pid_t pidTwo;

    pipe(pipeOne);
    pid = fork();

    waitOne = waitpid(pid, &stateOne, WUNTRACED);

    

}