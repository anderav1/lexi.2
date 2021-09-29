# Author: Lexi Anderson
# CS 4760
# Last modified: Sept 29, 2021
# Makefile (Project 2)

CC = gcc
CFLAGS = -g -Wall -Wshadow
TAR = runsim testsim
DEPS = runsim.c testsim.c license.c config.h
OBJ = runsim.o testsim.o license.o

all: runsim testsim

# generate main program executables
$(TAR): %: %.o license.o
	$(CC) $(CFLAGS) -o $@ $^

# generate object files from c files
$(OBJ): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

# clean up generated files
.PHONY: clean
clean:
	rm -f $(TAR) *.o
