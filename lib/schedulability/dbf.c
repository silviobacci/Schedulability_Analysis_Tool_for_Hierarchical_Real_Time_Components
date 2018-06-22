#include <utilities/utilities.h>

#include <schedulability/dbf.h>

double ulub_fp(taskset *ts) {
	return ts->size * ((2 ^ (1 / ts->size)) - 1);
}

int ulub_edf() {
	return 1;
}

unsigned int workload(taskset *ts, unsigned int i, unsigned int t) {
	unsigned int j, res = ts->tasks[i].C;
	
	for (j = 0; j < i; j++)
		res += my_ceil(t, ts->tasks[j].T) * ts->tasks[j].C;

	return res;
}

double dbf(taskset *ts, unsigned int t) {
	unsigned int i, res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += my_floor(t + ts->tasks[i].T - ts->tasks[i].D, ts->tasks[i].T) * ts->tasks[i].C;

	return res;
}
