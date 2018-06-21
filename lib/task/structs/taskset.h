#ifndef TASKSET_H
#define TASKSET_H

typedef struct taskset_ {
	unsigned int size;
	unsigned int is_deadline_costrained;
	task *tasks;
} taskset;

#endif
