CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAG= -O0 -Wall 

LIBS_DEP=lib_mm_overhead.o
LIBS=$(BIN_DIR)/lib_mm_overhead.o

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean time_example


pre-compile: 
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

time_example: $(LIBS_DEP) $(SRC_DIR)/time_example.c
	$(CC) -o $(BIN_DIR)/time_example $(LIBS) $(SRC_DIR)/time_example.c $(CFLAG)

lib_mm_overhead.o: pre-compile $(SRC_DIR)/lib_mm_overhead.c
	$(CC) -o $(BIN_DIR)/lib_mm_overhead.o -c $(SRC_DIR)/lib_mm_overhead.c

clean:
	rm -rf $(BIN_DIR)

