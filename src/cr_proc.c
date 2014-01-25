#include <stdio.h>
#include <unistd.h>
#include "bench.h"

#define LOOP_TIMES 1000
void benchmark_cr_proc() {
	int i, pid, delta;
	cpu_cycle before_call, son_after_call, father_after_call;
	for (i = 0; i < LOOP_TIMES; i++) {
		before_call = rdtsc();
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "fork error\n");
			exit(0);
		}
		else if (pid == 0) {
			son_after_call = rdtsc();
			delta = son_after_call - before_call;
			fprintf(stdout, "son delta = %d\n", delta);
			fflush(stdout);
			exit(0);
		}
		father_after_call = rdtsc();
		delta = father_after_call - before_call;
		fprintf(stdout, "father delta = %d\n", delta);
		fflush(stdout);
		wait(NULL);
	}
	fprintf(stderr, "create process overhead complete, check output \n");
}

