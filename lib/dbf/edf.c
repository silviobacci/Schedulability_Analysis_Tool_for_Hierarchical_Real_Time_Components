#include <task/task.h>
#include <task/taskset.h>
#include <dbf/edf.h>

static double my_max(double n1, double n2) {
	if(n1 > n2)
		return n1;
	return n2;
}

double dbf_edf(taskset *ts, unsigned int t) {
	unsigned int i;
	double res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += my_max(0.0, (((double) t + ts->tasks[i].P - ts->tasks[i].D) / ts->tasks[i].P)) * ts->tasks[i].C;

	return res;
}
