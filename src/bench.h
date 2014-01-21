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

double get_timing_overhead();
double get_loop_overhaead();

#endif

