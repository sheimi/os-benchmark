#include <stdio.h>
#include <stdlib.h>
#include "bench.h"

#define LOOP_OVERHEAD_TAG "CSE211_LOOP_OVERHEAD"
#define TIMEING_OVERHEAD_TAG "CSE211_TIMING_OVERHEAD"
#define LOOP_TIMES 10000000

static inline void setenv_double(char* tag, double d) {
  char env[32];
  sprintf(env, "%f", d);
  setenv(tag, env, true);
}

double get_timing_overhead() {
  int i;
  if (getenv(TIMEING_OVERHEAD_TAG)) {
    double overhead = atof(getenv(TIMEING_OVERHEAD_TAG));
    return overhead;
  }

  double timing_overhead = 0.0;
  _IN_LOOP_MM(timing_overhead, LOOP_TIMES, 1000, false, );
  setenv_double(TIMEING_OVERHEAD_TAG, timing_overhead);
  return timing_overhead;
}

double get_loop_overhaead() {
  int i;
  if (getenv(LOOP_OVERHEAD_TAG)) {
    double overhead = atof(getenv(LOOP_OVERHEAD_TAG));
    return overhead;
  }
  double loop_overhead;
  OUT_LOOP_MM(loop_overhead, LOOP_TIMES,);
  setenv_double(LOOP_OVERHEAD_TAG, loop_overhead);
  return loop_overhead;
}
