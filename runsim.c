// Author: Lexi Anderson
// Last modified: September 23, 2021
// Runsim.c

// runsim is invoked with the command:  runsim n < testing.data
	// n -- number of licenses


#include <stdio.h>
#include <sys/shm.h>
#include "license.h"

int main(int argc, char* argv[]) {
	int shmid;
	key_t key = 1996;  // name of shared memory segment
	char* shm;  // ptr to shared memory segment
	size_t shmsz;  // size of shared memory segment

	shmsz = sizeof(int);

	// create shared memory segment
	if ((shmid = shmget(key, shmsz, IPC_CREAT)) == -1) {
		perror("runsim: shmget: Failed to retrieve shared memory segment");
		exit(1);
	}

	// attach shmem seg to program's space
	if ((shm = shmat(shmid, NULL, 0)) == (char*)(-1)) {
		perror("runsim: shmat: Failed to attach shared memory segment");
		exit(1);
	}

	/* operate on the shared mem */

	int narg;

	if (argc != 2) {
		perror("runsim: argc: invalid argument count");
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



	// detach shmem seg from program space
	if ((shmdt(shm)) == -1) {
		perror("runsim: shmdt: Failed to detach shared memory segment");
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
bool choosing[n]; // shm
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
}

