#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <utilities/utilities.h>
#include <dbf/edf.h>

double dbf_edf(taskset *ts, unsigned int t) {
	unsigned int i;
	double res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += my_max(0.0, (((double) t + ts->tasks[i].P - ts->tasks[i].D) / ts->tasks[i].P)) * ts->tasks[i].C;

	return res;
}
