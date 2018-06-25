#ifndef CPU_H
#define CPU_H

#define ARRAY_SIZE_ALGORITHM	5

typedef struct cpu_ {
	unsigned int id;
	double max_u;
	double u;
	periodic_server * ps;
	taskset * ts;
} cpu;

#endif
