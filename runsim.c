// Author: Lexi Anderson
// CS 4760
// Last modified: Oct 4, 2021
// runsim.c -- main program executable

// runsim is invoked with the command:  runsim n < testing.data
	// n -- number of licenses


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include "config.h"

#define MAX_CANON 20
#define SHMKEY 101107 // shared memory segment key
#define SHMSZ sizeof(int)  // size of shared memory segment

extern int nlicenses;

char** tokenizestr(char* str);
void docommand(char* cline);

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
	if (initlicense() != 0) {
		perror("runsim: Error: initlicense");
		exit(1);
	}
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

/*TEST*/puts("runsim: Shared memory attached successfully");

	*shm = nlicenses;
/*TEST*/printf("runsim: The value of nlicenses stored in shared mem is %d\n", *shm);

	/* main loop */

	int status = 0;
	char inputBuffer[MAX_CANON];
	// read in one line at a time until EOF
	while (fgets(inputBuffer, MAX_CANON, stdin) != NULL) {
		// request a license
		getlicense();
		
		// which license functions do I need to call?
		// initlicense? getlicense? removelicenses?

		// fork child process that calls docommand
		pid_t pid, w;
		pid = fork();
		switch (pid) {
			case -1:  // error
				perror("runsim: Error: fork");
				exit(1);
			case 0:  // child
				puts("runsim: child process executing\n");
				docommand(inputBuffer);
				break;
			default:  // parent
				puts("runsim: parent process running\n");
				// check if any children have finished execution
				w = waitpid(pid, &status, WNOHANG);
				if (w == -1) {  // error
					perror("runsim: Error: waitpid");
					exit(1);
				} else if (w > 0) {  // success
					returnlicense();
				}
				break;
		}
	}

	// at EOF, wait for all children to finish
	while (*shm < narg) wait(&status);
	puts("runsim: All children have finished execution\n");
	return(0);

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

char** tokenizestr(char* str) {
	int maxSize = strlen(str);
	char** tokenarr = (char**)malloc(sizeof(char*)*maxSize);
	int i = 0;
	const char delims[] = {" "};
	char* token = strtok(str, delims);
	while (token != NULL) {
		tokenarr[i++] = token;
		token = strtok(str, delims);
	}
	// arr terminates with null
	tokenarr[i++] = NULL;

	// resize array if needed
	if (i < maxSize) {
		char** tokens = (char**)malloc(sizeof(char*)*i);
		for (int k = 0; k < i; k++) {
			tokens[k] = tokenarr[i];
		}
		free(tokenarr);
		return tokens;
	}

	return tokenarr;
}

void docommand(char* cline) {
	// request license
	getlicense();

	// get command from string
	//char** argv[strlen(cline)];
	char** argv = tokenizestr(cline);
	// exec the specified command
	execvp(argv[0], argv);
	free(argv);
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

