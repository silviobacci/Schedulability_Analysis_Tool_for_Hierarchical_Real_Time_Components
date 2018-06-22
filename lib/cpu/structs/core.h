#ifndef CORE_H
#define CORE_H

typedef struct core_ {
	unsigned int id;
	char * algorithm;
	double u;
	periodic_server * ps;
	taskset * ts;
} core;

#endif
