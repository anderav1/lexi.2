// Author: Lexi Anderson
// CS 4760
// Last modified: Sept 30, 2021
// runsim.c -- main program executable

// runsim is invoked with the command:  runsim n < testing.data
	// n -- number of licenses


#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include "config.h"

#define MAX_CANON 20
#define SHMKEY 101107 // shared memory segment key
#define SHMSZ sizeof(int)  // size of shared memory segment

extern int nlicenses;

// deallocate shared memory
void deallocshm(int shmid) {
	if (shmctl(shmid, IPC_RMID, NULL) == -1) {
		perror("runsim: Error: shmctl");
		exit(1);
	}
}


/* main function */

int main(int argc, char* argv[]) {
	// set nlicenses
	if (argc != 2) {
		perror("runsim: Error: argc");
		exit(1);
	}
	int narg = atoi(argv[1]);
	nlicenses = narg;


	/* allocate shared memory */
	int shmid;
	int* shm;  // ptr to shared memory segment

	// create shared memory segment
	if ((shmid = shmget(SHMKEY, SHMSZ, 0777 | IPC_CREAT)) == -1) {
		perror("runsim: Error: shmget");
		exit(1);
	}

	// attach shmem seg to program's space
	if ((shm = shmat(shmid, NULL, 0)) == (int*)(-1)) {
		perror("runsim: Error: shmat");
		deallocshm(shmid);
		exit(1);
	}

/*TEST*/puts("Shared memory attached successfully");

	*shm = nlicenses;
/*TEST*/printf("The value of nlicenses stored in shared mem is %d\n", *shm);

	/* main loop */

	char inputBuffer[MAX_CANON];
	// read in one line at a time until EOF
	while (fgets(inputBuffer, MAX_CANON, stdin)) {
		// request a license
		// which license functions do I need to call?
		// initlicense? getlicense? removelicenses?
	}
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
	if (shmdt(shm) == -1) {
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

