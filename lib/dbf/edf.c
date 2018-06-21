#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <utilities/utilities.h>
#include <dbf/edf.h>

int ulub_edf() {
	return 1;
}

double dbf(taskset *ts, unsigned int t) {
	unsigned int i, res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += my_floor(t + ts->tasks[i].T - ts->tasks[i].D, ts->tasks[i].T) * ts->tasks[i].C;

	return res;
}
