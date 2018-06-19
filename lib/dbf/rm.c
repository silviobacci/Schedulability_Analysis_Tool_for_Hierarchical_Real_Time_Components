#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <utilities/utilities.h>
#include <dbf/rm.h>

unsigned int dbf_rm(taskset *ts, unsigned int task_index, unsigned int t) {
	unsigned int i;
	unsigned int res = ts->tasks[task_index].C;
	
	for (i = 0; i < task_index; i++)
		res += my_ceil(t, ts->tasks[i].P) * ts->tasks[i].C;

	return res;
}
