#include <utilities/utilities.h>
#include <task/testing_set.h>
#include <schedulability/dbf.h>

#include <schedulability/s_analysis.h>

static unsigned int utilization_bound_fp(taskset *ts) {
	if(utilization_factor(ts) <= ulub_fp(ts))
		return 1;
	return 0;
}

static unsigned int rta_i(taskset *ts, unsigned int i) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
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

static unsigned int utilization_bound_edf(taskset *ts) {
	if(utilization_factor(ts) <= ulub_edf())
		return 1;
	return 0;
}

static unsigned int pda(taskset *ts) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int n_testing_set, i;

	n_testing_set = testing_set_edf(ts, testing_set);

	for (i = 0; i < n_testing_set; i++)
		if (dbf(ts, testing_set[i]) > testing_set[i])
			return 0;

	return 1;
}

unsigned int s_analysis_fp(taskset *ts) {
	if(!ts->is_deadline_costrained) {
		if(utilization_bound_fp(ts))
			return 1;	
	}
	
	return rta(ts);
}

unsigned int s_analysis_edf(taskset *ts) {
	if(ts->is_deadline_costrained)
		return pda(ts);
	return utilization_bound_edf(ts);
}
