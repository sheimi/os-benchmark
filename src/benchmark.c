#include "bench.h"
#include <stdio.h>

typedef void (*benchmark_func)();

typedef struct _benchmark {
  char name[32];
  benchmark_func func;
} benchmark_t;

benchmark_t benchmarks[] = {
  {"timing_overhead", benchmark_time_overhead},
  {"loop_overhead", benchmark_loop_overhead},
  {"", 0},
};

static inline void show_help() {
  fprintf(stdout, "Supported benchmarks:\n");
  benchmark_t *bm = benchmarks;
  while (bm->func != 0) {
    fprintf(stdout, "\t%s\n", bm->name);
    bm++;
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Too few arguments. please run \"benchmark help\" for help.\n");
    exit(1);
  }
  if (IS_EQUAL(argv[1], "help")) {
    show_help();
    exit(0);
  }
  benchmark_t *bm = benchmarks;
  while (bm->func != 0) {
    if (IS_EQUAL(argv[1], bm->name)) {
      bm->func();
      exit(0);
    }
    bm++;
  }
  fprintf(stderr, "No such benchmark. please run \"benchmark help\" for help.\n");
  exit(1);
  return 0;
}