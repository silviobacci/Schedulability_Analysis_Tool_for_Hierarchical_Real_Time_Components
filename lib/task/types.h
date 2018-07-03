#ifndef TASK_TYPES_H
#define TASK_TYPES_H

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_NUMBER_TASKS 	32		// maximum number of allowed tasks

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This structure contains the parameters of a periodic server
typedef struct periodic_server_ {
	unsigned int Qs;	// budget
	unsigned int Ts;	// period
} periodic_server;

// This structure contains the parameters desribing a task
typedef struct task_ {
	unsigned int id;	// identifier
	unsigned int C;		// computation time
	unsigned int D;		// deadline
	unsigned int T;		// period
} task;

// This structure containes the paramters describing a taskset
typedef struct taskset_ {
	unsigned int size;	// # of tasks contained in the set
	task *tasks;		// array of tasks
} taskset;

#endif
