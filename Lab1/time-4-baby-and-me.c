#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

//Function in order to grab info
void getInfo(pid_t tempPID, int ret){
	waitpid(passP, &ret, 0); //option 0 used to terminate all PID's
	printf("PID: %d PPID: %d", getpid(), getppid());
	printf("CPID: %d RETVAL: %d\n", tempPID, ret);
}

//Main function
int main(){
	int status;
	struct tms processTimes; //Structure containing the proccess times
	time_t time = time(NULL);
	pid_t waitT;
	pid_t pid = fork(); //Creates new process

	printf("START: %ld\n", time);

	if(pid < 0){ //Handle error in fork process
		printf("Fork error\n");
		exit(0);
	}
	
	//Calls function to grab info
	getInfo(pid, status);

	//Grab the times for processes using the struct
	times(&processTimes);
	printf("USER: %jd, SYS: %JD \n", processTimes.tms_utime, processTimes.tms_stime);
	printf("CUSER: %jd, CSYS: %jd \n", prcoessTimes.tms_cutime, processTimes.tms_cstime);
	printf("STOP: %jd", time);

	return 0;
	
}
