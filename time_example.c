#include <stdio.h>

typedef unsigned long long int tick;

#if defined(__i386__)
static __inline__ tick rdtsc(void) {
  tick x;
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}
#elif defined(__x86_64__)
static __inline__ tick rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ((tick) lo) | (((tick) hi) << 32);
}

#elif defined(__powerpc__)
static __inline__ tick rdtsc(void) {
  tick result=0;
  tick upper, lower,tmp;
  __asm__ volatile(
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

const long long int LOOP_TIMES = 10000000;

int main(int argc, char* argv[]) {
  int i;
  int delta;
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
