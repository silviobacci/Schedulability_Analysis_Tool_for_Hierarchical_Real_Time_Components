#include <stdio.h>

#include <task/task_io.h>
#include <task/testing_set.h>
#include <task/utilization_factor.h>
#include <utilities/utilities.h>
#include <h_analysis/fp.h>
#include <dbf/fp.h>
#include <sbf/sbf.h>

periodic_server * find_periodic_server_rm(taskset *ts) {
	unsigned int Ts = min_period(ts);
	unsigned int Qs = my_ceil(Ts * utilization_factor(ts), 1);
	return load_periodic_server(Qs, Ts);
}

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps) {
	unsigned int testing_set[MAX_SCHEDULING_POINTS], i;
	int j, n_testing_set;

	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0)
			for (j = 0; j < n_testing_set; j++)
				if (workload(ts, i, testing_set[j]) <= sbf(ps, testing_set[j])) 
					return 1;

	return 0;
}
