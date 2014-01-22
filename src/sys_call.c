#include <stdio.h>
#include <unistd.h>
#include "bench.h"

#define LOOP_TIMES 10000
int main() {
	int i, pid, delta;
	cpu_cycle before_call, after_call;
	for (i = 0; i < LOOP_TIMES; i++) {
		pid = fork();
		if (pid == 0) {
			before_call = rdtsc();
			getpid();
			after_call = rdtsc();
			delta = after_call - before_call;
			printf("delta = %d\n", delta);
			exit(0);
		}
		wait(NULL);
	}


	//printf("before_call = %lld\n", before_call);
	return 0;
}
