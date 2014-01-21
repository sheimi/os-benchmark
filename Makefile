CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAG= -O0 -Wall 

LIBS_DEP=lib_measure.o
LIBS=$(BIN_DIR)/lib_measure.o

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean time_example


pre-compile: 
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

time_example: $(LIBS_DEP) $(SRC_DIR)/time_example.c
	$(CC) -o $(BIN_DIR)/time_example $(LIBS) $(SRC_DIR)/time_example.c $(CFLAG)

lib_measure.o: pre-compile $(SRC_DIR)/lib_measure.c
	$(CC) -o $(BIN_DIR)/lib_measure.o -c $(SRC_DIR)/lib_measure.c

clean:
	rm -rf $(BIN_DIR)

