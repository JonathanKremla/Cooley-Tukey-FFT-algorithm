CC = gcc

FLAGS = -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g
DEPS = forkFFT.h
OBJ = forkFFT.o funcDef.o

.PHONY: all clean
all: forkFFT

forkFFT: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -rf *.o forkFFT