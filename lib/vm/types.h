#ifndef VM_TYPES_H
#define VM_TYPES_H

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_NUMBER_CPUS 16		// maximum allowed number of cpus in a vm

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This structure contains all the paramters for describing a cpu
typedef struct cpu_ {
	unsigned int id;		// cpu identifier
	double max_u;			// max allowed u on a cpu
	double u;				// current u of the cpu
	periodic_server * ps;	// periodic server running for our component
	taskset * ts;			// tasks allocated to the cpu
} cpu;

// This strctures containes all the paramters to describe a vm
typedef struct vm_ {
	unsigned int n_cpus;	// # of cpus
	unsigned int ps_set;	// 1 if a periodic server is specified, 0 otherwise
	cpu * cpus;				// array of cpus
} vm;

#endif
