CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAG= -O0 -Wall -Winline -fno-omit-frame-pointer -funroll-loops

<<<<<<< HEAD
LIBS=$(BIN_DIR)/measurement.o\
		 $(BIN_DIR)/proc_call.o\
		 $(BIN_DIR)/sys_call.o\
		 $(BIN_DIR)/cr_proc.o\
		 $(BIN_DIR)/cr_thread.o\
		 $(BIN_DIR)/context_switch.o
LIBS_DEP=measurement.o\
				 proc_call.o\
				 sys_call.o\
				 cr_proc.o\
				 cr_thread.o\
				 context_switch.o

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean benchmark

pre-compile: 
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

benchmark: $(LIBS_DEP) $(SRC_DIR)/benchmark.c
	$(CC) -o $(BIN_DIR)/benchmark $(LIBS) $(SRC_DIR)/benchmark.c $(CFLAG)

measurement.o: pre-compile $(SRC_DIR)/measurement.c
	$(CC) -o $(BIN_DIR)/measurement.o -c $(SRC_DIR)/measurement.c $(CFLAG)

proc_call.o: pre-compile $(SRC_DIR)/proc_call.c
	$(CC) -o $(BIN_DIR)/proc_call.o -c $(SRC_DIR)/proc_call.c $(CFLAG)

sys_call.o: pre-compile $(SRC_DIR)/sys_call.c
	$(CC) -o $(BIN_DIR)/sys_call.o -c $(SRC_DIR)/sys_call.c

cr_proc.o: pre-compile $(SRC_DIR)/cr_proc.c
	$(CC) -o $(BIN_DIR)/cr_proc.o -c $(SRC_DIR)/cr_proc.c

cr_thread.o: pre-compile $(SRC_DIR)/cr_thread.c
	$(CC) -o $(BIN_DIR)/cr_thread.o -c $(SRC_DIR)/cr_thread.c

context_switch.o: pre-compile $(SRC_DIR)/context_switch.c
	$(CC) -o $(BIN_DIR)/context_switch.o -c $(SRC_DIR)/context_switch.c $(CFLAG)

clean:
	rm -rf $(BIN_DIR)

