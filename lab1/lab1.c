#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

//Function in order to grab info
void getInfo(pid_t tempPID, int ret){	
	/*waitpid(tempPID, &ret, 0); //option 0 used to terminate all PID's
	printf("PID: %d , PPID: %d \n", getpid(), getppid());
	printf("CPID: %d , RETVAL: %d ", tempPID, ret);
	
	if(tempPID == 0){
		printf("\n");
		exit(0);
	}
	else{
		printf("CPID: %d , RETVAL: %d", tempPID, ret);
	}
	*/

	//PID was created
	if(tempPID == 0){
		printf("PPID: %u, PID: %u\n",getppid(),getpid());
		exit(0);
	}
	//Grab child info
	else{
		int status;
		pid_t waitP = waitpid(tempPID,&status,0);
		printf("PPID: %u, PID: %u, CPID: %u, RETVAL: %d\n",getppid(),getpid(),tempPID,status);
	}

}

//Main function
int main(){
	int status;
	struct tms processTimes; //Structure containing the proccess times
	time_t timeV = time(NULL);
	//pid_t waitT;

	printf("START: %ld\n", timeV);

	pid_t pid = fork(); //Creates new process

	if(pid < 0){ //Handle error in fork process
		printf("Fork error\n");
		exit(0);
	}
	
	//Calls function to grab info
	getInfo(pid, status);

	//Grab the times for processes using the struct
	times(&processTimes);
	printf("USER: %jd, SYS: %jd \n", processTimes.tms_utime, processTimes.tms_stime);
	printf("CUSER: %jd, CSYS: %jd \n", processTimes.tms_cutime, processTimes.tms_cstime);
	printf("STOP: %jd \n", timeV);

	return 0;
	
}
