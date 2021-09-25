CC = gcc
CFLAGS = -g -Wall -Wshadow
TAR = runsim testsim
DEPS = runsim.c testsim.c license.c config.h
OBJ = runsim.o testsim.o license.o

all: runsim testsim

#runsim: runsim.o $(DEPS)
#	$(CC) $(CFLAGS) -o $@ $^

#testsim: testsim.o $(DEPS)
#	$(CC) $(CFLAGS) -o $@ $^

# generate main program executables
$(TAR): %: %.o $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

# generate object files from c files
$(OBJ): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

# clean up generated files
.PHONY: clean
clean:
	rm -f $(TAR) *.o
