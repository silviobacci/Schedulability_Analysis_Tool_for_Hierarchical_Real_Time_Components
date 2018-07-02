#ifndef PERIODIC_SERVER_H
#define PERIODIC_SERVER_H

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This structure contains the parameters of a periodic server
typedef struct periodic_server_ {
	unsigned int Qs;	// budget
	unsigned int Ts;	// period
} periodic_server;

#endif
