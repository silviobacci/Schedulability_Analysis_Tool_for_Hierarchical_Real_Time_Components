#include <task/task.h>
#include <task/taskset.h>
#include <dbf/rm.h>

static unsigned int my_ceil(unsigned int n, unsigned int d) {
	unsigned int q = n / d;
	
	if (q * d == n) 
		return q;
	
	return q + 1;
}

unsigned int dbf_rm(taskset *ts, unsigned int task_index, unsigned int t) {
	unsigned int i;
	unsigned int res = ts->tasks[task_index].C;
	
	for (i = 0; i < task_index; i++)
		res += my_ceil(t, ts->tasks[i].P) * ts->tasks[i].C;

	return res;
}
