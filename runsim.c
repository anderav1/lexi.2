// Author: Lexi Anderson
// CS 4760
// Last modified: Sept 29, 2021
// runsim.c -- main program executable

// runsim is invoked with the command:  runsim n < testing.data
	// n -- number of licenses


#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "config.h"

#define MAX_CANON 20

extern int nlicenses;

int main(int argc, char* argv[]) {
	/* allocate shared memory */
	int shmid;
	key_t key = 1996;  // name of shared memory segment
	char* shm;  // ptr to shared memory segment
	size_t shmsz;  // size of shared memory segment

	shmsz = sizeof(int);

	// create shared memory segment
	if ((shmid = shmget(key, shmsz, IPC_CREAT)) == -1) {
		perror("runsim: Error: shmget");
		exit(1);
	}

	// attach shmem seg to program's space
	if ((shm = shmat(shmid, NULL, 0)) == (char*)(-1)) {
		perror("runsim: Error: shmat");
		deallocshm(shmid);
		exit(1);
	}


	/* operate on the shared mem */
	int narg;
	if (argc != 2) {
		perror("runsim: Error: argc");
		exit(1);
	}
	narg = atoi(argv[1]);
	// set license obj ptr to point to narg

	// read in command line args
	// validate args; output usage msg if invalid arg

	// set up shared memory
		// see commands shmget, shmctl, shmat, shmdt
	// set up func to deallocate shared memory
		// use command ipcs to ensure that shared mem is allocated
		// and deallocated correctly

	// run loop until we reach eof in stdin
		// use fgets to read a string from stdin
		// request a license from license obj
		// fork a child that calls docommand
		// docommand requests license from license manager obj
		// if license is unavailable, wait until available
		// pass the string from fgets to docommand
		// docommand will execl the specified command
		// parent runsim process checks if any children have finished
			// and returnlicense when that happens
		// when eof of stdin is encountered, wait for all 
			// remaining children to finish before exiting

	// fork and exec a child
	// have the child attach to and read shared mem

	// implement signal handling to terminate after a specified num of secs
		// test by sending child into infinite loop

	// fork and exec multiple children until the specific limits

	// each child process runs execl testsim

	deallocshm(shmid);

	/* detach shared mem seg from program space */
	if ((shmdt(shm)) == -1) {
		perror("runsim: Error: shmdt");
		exit(1);
	}
}

void docommand(char* cline) {
	// fork a child (grandchild of the og) that calls makeargv on cline
	// and calls execvp on the resulting arg array

	// wait for this child, then return the license to the license obj

	// exit
}

//
// bakery algorithm
/* bool choosing[n]; // shm
int number[n];  // shm, contains turn numbers

void process_i(const int i) {
	do {
		choosing[i] = true;
		number[i] = 1 + max(number);
		choosing[i] = false;

		for (int j = 0; j < n; j++) {
			while (choosing[j]);
			while ((number[j]) && (number[j], j) < (number[i], i));
		}

		critical_section();

		number[i] = 0;

		remainder_section();
	} while (1);
}*/

// deallocate shared memory
void deallocshm(int shmid) {
	if ((shmctl(shmid, IPC_RMID, NULL)) == -1) {
		perror("runsim: Error: shmctl");
		exit(1);
	}
}
