#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>

void print_utilization_factor(double U) {
	printf("The utilization factor of the taskset is:\n\t U = %f\n", U);
}

double utilization_factor(taskset *ts) {
	unsigned int i;
	double U = 0;

	for(i = 0; i < ts->size; i++)
		U += (double) ts->tasks[i].C / ts->tasks[i].T;
	
	return U;
}
