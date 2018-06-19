#include <task/task.h>
#include <task/taskset.h>
#include <task/scheduling_points.h>
#include <dbf/rm.h>

unsigned int tda_rm_n(taskset *ts, unsigned int task_index) {
	unsigned int sp[MAX_SCHEDULING_POINTS];
	int n_sp, i;

	n_sp = scheduling_points(ts, task_index, sp, MAX_SCHEDULING_POINTS);

	for (i = 0; i < n_sp; i++)
		if (dbf_rm(ts, task_index, sp[i]) <= sp[i])
			return 1;

	return 0;
}

unsigned int tda_rm(taskset *ts) {
	unsigned int i;

	for(i = 0; i < ts->size; i++)
		if(!tda_rm_n(ts, i))
			return 0;

	return  1;
}
