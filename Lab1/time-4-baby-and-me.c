#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	struct tms processTimes;
	time_t time = time(NULL);
	pid_t waitT;
	pid_t pid = fork();

	printf("START: %ld\n", time);
}
