#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "bench.h"
#include <sys/wait.h>

#define LOOP_TIMES 10000
void benchmark_sys_call() {
	int i, pid;
	cpu_cycle before_call, after_call, delta;
	for (i = 0; i < LOOP_TIMES; i++) {
		/*pid = fork();
		if (pid == 0) {*/
			before_call = rdtsc();
			syscall(SYS_getpid);
			after_call = rdtsc();
			delta = after_call - before_call;
			fprintf(stdout, "delta = %llu\n", delta);
			fflush(stdout);
			/*exit(0);
		}
		wait(NULL);*/
	}
	fprintf(stderr, "syscall overhead complete, check output \n");
  int i, pid, delta;
  cpu_cycle before_call, after_call;
  for (i = 0; i < LOOP_TIMES; i++) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "fork error\n");
      exit(0);
    }
    else if (pid == 0) {
      before_call = rdtsc();
      getpid();
      after_call = rdtsc();
      delta = after_call - before_call;
      fprintf(stdout, "delta = %d\n", delta);
      fflush(stdout);
      exit(0);
    }
    wait(NULL);
  }
  fprintf(stderr, "syscall overhead complete, check output \n");
}

