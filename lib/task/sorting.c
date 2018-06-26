#include <stdlib.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>

void sort_taskest_by_id(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].id > ts->tasks[j + 1].id) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_periods(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].T > ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_deadlines(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].D > ts->tasks[j + 1].D) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_utilization_factor(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if ((double) ts->tasks[j].C / ts->tasks[j].T > (double) ts->tasks[j + 1].C / ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_periods(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].T < ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_deadlines(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].D < ts->tasks[j + 1].D) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_utilization_factor(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if ((double) ts->tasks[j].C / ts->tasks[j].T < (double) ts->tasks[j + 1].C / ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}
