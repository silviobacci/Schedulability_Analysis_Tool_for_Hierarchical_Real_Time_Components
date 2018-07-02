#ifndef VM_H
#define VM_H

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_NUMBER_CPUS 16		// maximum allowed number of cpus in a vm

//------------------------------------------------------------------------------
// GLOBAL DATA STRUCTURES
//------------------------------------------------------------------------------

// This enums contains all the allwoed bin packing algorhtms
typedef enum a_algorithm_ {BF, FF, NF, WF, FFD} a_algorithm;

// This strctures containes all the paramters to describe a vm
typedef struct vm_ {
	unsigned int n_cpus;	// # of cpus
	unsigned int ps_set;	// 1 if a periodic server is specified, 0 otherwise
	cpu * cpus;				// array of cpus
} vm;

#endif
