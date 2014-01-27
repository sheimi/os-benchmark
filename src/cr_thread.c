#include <stdio.h>
#include <pthread.h>
#include "bench.h"

#define LOOP_TIMES 10000

void *foo(void *ptr) {
	cpu_cycle thread_call = rdtsc();
	fprintf(stdout, "thread run delta = %llu\n",
		thread_call - (cpu_cycle)(ptr));
	pthread_exit(NULL);
}

void benchmark_cr_thread() {
	pthread_t thread;
	int i, delta, iret;
	cpu_cycle before_call, after_call;
	for (i = 0; i < LOOP_TIMES; i++) {
		before_call = rdtsc();
		iret = pthread_create(&thread, NULL,
			foo, (void*)before_call);
		after_call = rdtsc();
		delta = after_call - before_call;
		fprintf(stdout, "father delta = %d\n", delta);
		pthread_join(thread, NULL);
	}
	fprintf(stderr, "create process overhead complete, check output \n");
}

