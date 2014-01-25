#include <stdio.h>
#include <unistd.h>
#include "bench.h"

#define LOOP_TIMES 10000
void benchmark_sys_call() {
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

