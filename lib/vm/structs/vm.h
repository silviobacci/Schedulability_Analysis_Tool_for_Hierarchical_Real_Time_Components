#ifndef VM_H
#define VM_H

#define MAX_NUMBER_CPUS 16

typedef enum a_algorithm_ {BF, FF, NF, WF, FFD} a_algorithm;

typedef struct vm_ {
	unsigned int n_cpus;
	cpu * cpus;
} vm;

#endif
