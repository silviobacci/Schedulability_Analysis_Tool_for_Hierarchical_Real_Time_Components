#ifndef CPU_H
#define CPU_H	

//------------------------------------------------------------------------------
// GLOBAL DATA STRUCTURES
//------------------------------------------------------------------------------

// This structure contains all the paramters for describing a cpu
typedef struct cpu_ {
	unsigned int id;		// cpu identifier
	double max_u;			// max allowed u on a cpu
	double u;				// current u of the cpu
	periodic_server * ps;	// periodic server running for our component
	taskset * ts;			// tasks allocated to the cpu
} cpu;

#endif
