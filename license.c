// Author: Lexi Anderson
// CS 4760
// license.c

#include <stdlib.h>
#include "config.h"

int nlicenses = 0; // initial value set to 0

// Getlicense function
// Blocks until a license is available
int getlicense() {
	while (nlicenses == 0);
	return(0);
}

// Returnlicense function
// Increments the number of available licenses
int returnlicense() {
	nlicenses++;
	return(0);
}

// Initlicense function
// Performs any needed initialization of the license obj
int initlicense() {
	// do smtg

	return(0);
}

// Addtolicenses function
// Adds n licenses to the number available
void addtolicenses(int n) {
	nlicenses += n;
}

// Removelicenses function
// Decrements the number of licenses by n
void removelicenses(int n) {
	nlicenses -= n;
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
