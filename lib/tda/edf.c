#include <task/task.h>
#include <task/taskset.h>
#include <task/scheduling_points.h>
#include <dbf/edf.h>

unsigned int tda_edf(taskset *ts) {
	unsigned int sp[MAX_SCHEDULING_POINTS], i, max_period = 0, thread_index = 0;
	int n_sp, j;

	for (i = 0; i < ts->size; i++)
		if(ts->tasks[i].P > max_period) {
			max_period = ts->tasks[i].P;
			thread_index = i;
		}

	n_sp = scheduling_points(ts, thread_index, sp, MAX_SCHEDULING_POINTS);

	for (j = 0; j < n_sp; j++)
		if (dbf_edf(ts, sp[i]) > sp[i])
			return 0;

	return 1;
}
