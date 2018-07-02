#ifndef TASKSET_H
#define TASKSET_H

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_NUMBER_TASKS 	32		// maximum number of allowed tasks

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This enum contains all the scheduling algorithms supported
typedef enum s_algorithm_ {FP, RM, DM, EDF} s_algorithm;

// This structure containes the paramters describing a taskset
typedef struct taskset_ {
	unsigned int size;				// # of tasks contained in the set
	unsigned int D_less_than_T;		// 1 if D < T, 0 otherwise
	task *tasks;					// array of tasks
} taskset;

#endif
