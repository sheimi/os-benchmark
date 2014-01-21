#include <stdio.h>
#include <stdlib.h>
#include "bench.h"

#define LOOP_OVERHEAD_TAG "CSE211_LOOP_OVERHEAD"
#define TIMEING_OVERHEAD_TAG "CSE211_TIMING_OVERHEAD"
#define LOOP_TIMES 10000000

double get_timing_overhead() {
  int i;
  if (getenv(TIMEING_OVERHEAD_TAG)) {
    double overhead = atof(getenv(TIMEING_OVERHEAD_TAG));
    return overhead;
  }

  int delta = 0;
  for (i = 0; i < LOOP_TIMES; i++) {
    cpu_cycle cpu_cycle1= rdtsc();
    cpu_cycle cpu_cycle2= rdtsc();
    delta += cpu_cycle2 - cpu_cycle1;
  }
  double overhead = delta * 1.0 / LOOP_TIMES;
  char env[32];
  sprintf(env, "%f", overhead);
  setenv(TIMEING_OVERHEAD_TAG, env, true);
  return overhead;
}

double get_loop_overhaead() {
  int i;
  if (getenv(LOOP_OVERHEAD_TAG)) {
    double overhead = atof(getenv(LOOP_OVERHEAD_TAG));
    return overhead;
  }

  int before_loop = rdtsc();
  for (i = 0; i < LOOP_TIMES; i++);
  int end_loop = rdtsc();
  double timing_overehad = get_timing_overhead();
  double loop_overhead = (end_loop - before_loop - timing_overehad) / LOOP_TIMES;
  char env[32];
  sprintf(env, "%f", loop_overhead);
  setenv(LOOP_OVERHEAD_TAG, env, true);
  return loop_overhead;
}
