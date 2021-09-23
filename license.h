#ifndef LICENSE_H
#define LICENSE_H


int getlicense(void);	// blocks until a license is available
int returnlicense(void);  // increments the number of available licenses
int initlicense(void); 	// performs any need initialization of the license object
addtolicenses(int n);  // adds n licenses to the number available
removelicenses(int n);  // decrements the number of licenses by n
logmsg(const char* msg);  // write the specified message to the log file

#endif

