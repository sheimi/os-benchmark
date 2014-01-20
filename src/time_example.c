#include <stdio.h>
#include "bench.h"

const long long int LOOP_TIMES = 10000000;

int main(int argc, char* argv[]) {
  int i;
  int delta = 0;
  for (i = 0; i < LOOP_TIMES; i++) {
    tick tick1= rdtsc();
    tick tick2= rdtsc();
    delta += tick2 - tick1;
  }
  double rdtsc_overhead = delta * 1.0 / LOOP_TIMES;
  printf("readtime overhead: %f\n", rdtsc_overhead);

  int before_loop = rdtsc();
  for (i = 0; i < LOOP_TIMES; i++) {
  }
  int end_loop = rdtsc();
  double loop_overhead = (end_loop - before_loop - rdtsc_overhead) * 1.0 / LOOP_TIMES;
  printf("loop overhead: %f\n", loop_overhead);
}
