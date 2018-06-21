#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/utilization_factor.h>
#include <task/testing_set.h>
#include <utilities/utilities.h>
#include <dbf/edf.h>

static unsigned int utilization_bound(taskset *ts) {
	if(utilization_factor(ts) <= ulub_edf())
		return 1;
	return 0;
}

static unsigned int pda(taskset *ts) {
	unsigned int testing_set[MAX_SCHEDULING_POINTS];
	int n_testing_set, i;

	n_testing_set = testing_set_edf(ts, testing_set);

	for (i = 0; i < n_testing_set; i++)
		if (dbf(ts, testing_set[i]) > testing_set[i])
			return 0;

	return 1;
}

unsigned int s_analysis_edf(taskset *ts) {
	printf("sono qui\n");
	if(ts->is_deadline_costrained)
		return pda(ts);
	return utilization_bound(ts);
}
