#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/scheduling_points.h>
#include <utilities/utilities.h>
#include <dbf/edf.h>

unsigned int tda_edf(taskset *ts) {
	unsigned int sp[MAX_SCHEDULING_POINTS];
	int n_sp, i;

	n_sp = scheduling_points(ts, task_with_max_period(ts), sp, MAX_SCHEDULING_POINTS);

	for (i = 0; i < n_sp; i++)
		if (dbf_edf(ts, sp[i]) > sp[i])
			return 0;

	return 1;
}
