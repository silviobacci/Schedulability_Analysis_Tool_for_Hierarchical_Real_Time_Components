#include <math.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <schedulability/dbf.h>

unsigned int workload(taskset *ts, unsigned int i, unsigned int t) {
	unsigned int j, res = ts->tasks[i].C;
	
	for (j = 0; j < i; j++)
		res += (unsigned int) ceil((double) t / ts->tasks[j].T) * ts->tasks[j].C;

	return res;
}

double pdf(taskset *ts, unsigned int t) {
	unsigned int i, res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += (unsigned int) floor((double) (t + ts->tasks[i].T - ts->tasks[i].D) / ts->tasks[i].T) * ts->tasks[i].C;

	return res;
}
