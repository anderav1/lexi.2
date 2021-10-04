// Author: Lexi Anderson
// CS 4760
// Last modified: Oct 4, 2021
// license.c

#include <stdlib.h>
#include <stdio.h>
#include "config.h"

int nlicenses = 0; // number of available licenses

// Getlicense function
// Blocks until a license is available
// Returns 0 for success
int getlicense() {
	while (nlicenses == 0);  // wait for license to become available
	removelicenses(1);  // decrement nlicenses
	printf("License taken. %d now available\n", nlicenses);
	return(0);
}

// Returnlicense function
// Increments the number of available licenses
// Returns 0 for success
int returnlicense() {
	addtolicenses(1);
	return(0);
}

// Initlicense function
// Performs initialization of the license obj
// Returns 0 upon success
int initlicense() {
	// do smtg???
	printf("License obj initialized. %d available\n", nlicenses);
	return(0);
}

// Addtolicenses function
// Adds n licenses to the number available
void addtolicenses(int n) {
	printf("%d licenses available before, ", nlicenses);
	nlicenses += n;
	printf("%d licenses returned, ", n);
	printf("%d available now\n", nlicenses);
}

// Removelicenses function
// Decrements the number of licenses by n
void removelicenses(int n) {
	printf("%d licenses available before, ", nlicenses);
	nlicenses -= n;
	printf("%d licenses removed, ", n);
	printf("%d available now\n", nlicenses);
}

// Logmsg function
// Writes the specified message to the log file
// Log file treated as critical resource
void logmsg(const char* msg) {
	// check if file is available

	// open file

	// append msg to file

	// close file
}
