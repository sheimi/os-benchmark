#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include "bench.h"

#define LOOP_TIMES 100

void dommap(int fd, int size) {
	char c, *bufp;
	int i, j;
	cpu_cycle t1, t2; 
	bufp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
	if (bufp == (void *)-1)
		fprintf(stderr, "mmap error: %s \n", strerror(errno));
	// Start measuring
	for (i = 0, j=0; i < LOOP_TIMES; i++,j+=4096) {
		t1 = rdtsc();
		c = bufp[j];
		t2 = rdtsc();
		printf("%c, %lld\n", c, t2-t1);
	}   
	munmap(bufp, size);
}
void benchmark_page_fault() {
	int fd, pagesize;
	struct stat stat;
	system("fallocate -l 1M file.txt");
	if ((fd = open("file.txt", O_RDWR, 0)) < 0)
		fprintf(stderr, "open file error\n");
	fstat(fd, &stat);
	printf("file size = %lld\n", stat.st_size);
	pagesize = getpagesize();
	printf("page size = %d\n", pagesize);

	dommap(fd, stat.st_size);
	close(fd);
	system("rm file.txt");
}

