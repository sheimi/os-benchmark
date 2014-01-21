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
  _OUT_LOOP_MM(loop_overhead, LOOP_TIMES, false, );
  setenv_double(LOOP_OVERHEAD_TAG, loop_overhead);
  return loop_overhead;
}

#define PC(i) proc_call_##i
static void PC(0)() {}
static void PC(1)(int p0) {}
static void PC(2)(int p0, int p1) {}
static void PC(3)(int p0, int p1, int p2) {}
static void PC(4)(int p0, int p1, int p2, int p3) {}
static void PC(5)(int p0, int p1, int p2, int p3, int p4) {}
static void PC(6)(int p0, int p1, int p2, int p3, int p4, int p5) {}
static void PC(7)(int p0, int p1, int p2, int p3, int p4, int p5, int p6) {}

const int MAX_PROC_CALL_CYCLE = 1000;
double proc_call_overhead(int arg_count) {
  double overhead;
  switch(arg_count) {
    default:
    case 0:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(0)());
      break;
    case 1:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(1)(1));
      break;
    case 2:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(2)(1, 2));
      break;
    case 3:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(3)(1, 2, 3));
      break;
    case 4:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(4)(1, 2, 3, 4));
      break;
    case 5:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(5)(1, 2, 3, 4, 5));
      break;
    case 6:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(6)(1, 2, 3, 4, 5, 6));
      break;
    case 7:
      IN_LOOP_MM(overhead, LOOP_TIMES, MAX_PROC_CALL_CYCLE, PC(7)(1, 2, 3, 4, 5, 6, 7));
      break;
  }
  return overhead;
}
