CC       := gcc
MPICC    := mpicc
CFLAGS   := -O2 -Wall
LDFLAGS  := -lm

SERIAL_DIR   := Serial
PARALLEL_DIR := Parallel

SERIAL_SRC   := $(SERIAL_DIR)/serial.c
PARALLEL_SRC := $(PARALLEL_DIR)/parallel.c

SERIAL_BIN   := serial
PARALLEL_BIN := parallel

.PHONY: all clean

all: $(SERIAL_BIN) $(PARALLEL_BIN)

$(SERIAL_BIN): $(SERIAL_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(PARALLEL_BIN): $(PARALLEL_SRC)
	$(MPICC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(SERIAL_BIN) $(PARALLEL_BIN)
