#ifndef TASK_H
#define TASK_H

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This structure contains the parameters desribing a task
typedef struct task_ {
	unsigned int id;	// identifier
	unsigned int C;		// computation time
	unsigned int D;		// deadline
	unsigned int T;		// period
} task;

#endif
