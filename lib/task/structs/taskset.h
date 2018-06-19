#ifndef TASKSET_H
#define TASKSET_H

typedef struct taskset_ {
	unsigned int size;
	task *tasks;
} taskset;

#endif
