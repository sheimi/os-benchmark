CC=gcc
BIN=bin
SRC=src
CFLAG= -O0 -Wall 

ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
endif

all: clean time_example


pre-compile: 
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

time_example: pre-compile $(SRC)/time_example.c
	$(CC) -o $(BIN)/time_example $(SRC)/time_example.c $(CFLAG)

clean:
	rm -rf $(BIN)

