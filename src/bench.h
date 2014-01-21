#ifndef BENCH_H
#define BENCH_H

typedef unsigned long long int cpu_cycle;

#define true 1
#define false 0

#if defined(__i386__)
static inline cpu_cycle rdtsc(void) {
  cpu_cycle x;
  asm volatile (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}
#elif defined(__x86_64__)
static inline cpu_cycle rdtsc(void) {
  unsigned hi, lo;
  asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
  return ((cpu_cycle) lo) | (((cpu_cycle) hi) << 32);
}

#elif defined(__powerpc__)
static inline cpu_cycle rdtsc(void) {
  cpu_cycle result=0;
  cpu_cycle upper, lower,tmp;
  asm volatile(
                "0:                  \n"
                "\tmftbu   %0           \n"
                "\tmftb    %1           \n"
                "\tmftbu   %2           \n"
                "\tcmpw    %2,%0        \n"
                "\tbne     0b         \n"
                : "=r"(upper),"=r"(lower),"=r"(tmp)
              );
  result = upper;
  result = result << 32;
  result = result | lower;

  return (result);
}
#endif

#define OUT_LOOP_MM(out, loop_count, block) {         \
      int i;                                          \
      double _timing_overehad = get_timing_overhead();\
      cpu_cycle before_loop = rdtsc();                \
      for (i = 0; i < loop_count; i++) {              \
        block;                                        \
      }                                               \
      cpu_cycle end_loop = rdtsc();                        \
      out = (end_loop - before_loop - _timing_overehad) / LOOP_TIMES; \
    }

#define _IN_LOOP_MM(out, loop_count, max, include_timing, block) {\
      int i;                                          \
      int real_loop = loop_count;                     \
      unsigned long long delta = 0;                   \
      double _t_overhead = 0.0;                       \
      if (include_timing) {                           \
        timing_overhead = get_timing_overhead();      \
      }                                               \
      for (i = 0; i < loop_count; i++) {              \
        cpu_cycle before_op = rdtsc();                \
        block;                                        \
        cpu_cycle end_op = rdtsc();                   \
        cpu_cycle delta_op = end_op - before_op;      \
        if ((delta_op < max) && (delta_op > 0)) {     \
          delta += delta_op;                          \
        } else {                                      \
          real_loop--;                                \
        }                                             \
      }                                               \
      out = delta * 1.0 / real_loop - _t_overhead;    \
    }

#define IN_LOOP_MM(out, loop_count, max, block)  _IN_LOOP_MM(out, loop_count, max, true, block)

double get_timing_overhead();
double get_loop_overhaead();

#endif

