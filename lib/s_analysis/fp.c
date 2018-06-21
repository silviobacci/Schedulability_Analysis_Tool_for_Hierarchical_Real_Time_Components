#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/testing_set.h>
#include <task/utilization_factor.h>
#include <dbf/fp.h>

static unsigned int utilization_bound(taskset *ts) {
	if(utilization_factor(ts) <= ulub_fp(ts))
		return 1;
	return 0;
}

static unsigned int rta_i(taskset *ts, unsigned int i) {
	unsigned int testing_set[MAX_SCHEDULING_POINTS];
	int n_testing_set, j;

	n_testing_set = testing_set_fp(ts, testing_set, i);

	for (j = 0; j < n_testing_set; j++)
		if (workload(ts, i, testing_set[i]) <= testing_set[i])
			return 1;

	return 0;
}

static unsigned int rta(taskset *ts) {
	unsigned int i;
	
	for(i = 0; i < ts->size; i++)
		if(!rta_i(ts, i))
			return 0;

	return  1;
}

unsigned int s_analysis_fp(taskset *ts) {
	if(!ts->is_deadline_costrained) {
		if(utilization_bound(ts))
			return 1;	
	}
	
	return rta(ts);
}
