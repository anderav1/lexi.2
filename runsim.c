// Author: Lexi Anderson
// Last modified: September 23, 2021
// Runsim.c

// runsim is invoked with the command:  runsim n < testing.data
	// n -- number of licenses


#include <stdio.h>
#include <sys/shm.h>

int main(int argc, char* argv[]) {
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

}
