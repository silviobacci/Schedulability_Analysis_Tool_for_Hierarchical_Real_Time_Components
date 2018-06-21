#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <utilities/utilities.h>
#include <dbf/fp.h>

double ulub_fp(taskset *ts) {
	return ts->size * ((2 ^ (1 / ts->size)) - 1);
}

unsigned int workload(taskset *ts, unsigned int i, unsigned int t) {
	unsigned int j, res = ts->tasks[i].C;
	
	for (j = 0; j < i; j++)
		res += my_ceil(t, ts->tasks[j].T) * ts->tasks[j].C;

	return res;
}
