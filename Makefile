CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAG= -O0 -Wall 

LIBS=$(BIN_DIR)/measurement.o
LIBS_DEP=measurement.o

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean benchmark

pre-compile: 
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

benchmark: $(LIBS_DEP) $(SRC_DIR)/benchmark.c
	$(CC) -o $(BIN_DIR)/benchmark $(LIBS) $(SRC_DIR)/benchmark.c $(CFLAG)

measurement.o: pre-compile $(SRC_DIR)/measurement.c
	$(CC) -o $(BIN_DIR)/measurement.o -c $(SRC_DIR)/measurement.c

clean:
	rm -rf $(BIN_DIR)

