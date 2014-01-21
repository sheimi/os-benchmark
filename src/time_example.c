#include <stdio.h>
#include "bench.h"

int main(int argc, char* argv[]) {
  printf("readtime overhead: %f\n", get_timing_overhead());
  printf("loop overhead: %f\n", get_loop_overhaead());
  return 0;
}
