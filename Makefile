CC=gcc
BIN=bin
CFLAG= -O0 -Wall 

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean time_example


pre-compile: 
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

time_example: pre-compile time_example.c
	$(CC) -o $(BIN)/time_example time_example.c $(CFLAG)

clean:
	rm -rf $(BIN)

