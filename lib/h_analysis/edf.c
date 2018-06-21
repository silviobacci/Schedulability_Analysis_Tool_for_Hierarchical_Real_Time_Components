#include <stdio.h>

#include <task/task_io.h>
#include <task/testing_set.h>
#include <task/utilization_factor.h>
#include <utilities/utilities.h>
#include <h_analysis/edf.h>
#include <dbf/edf.h>
#include <sbf/sbf.h>

periodic_server * find_periodic_server_edf(taskset *ts) {
	unsigned int Ts = min_period(ts);
	unsigned int Qs = my_ceil(Ts * utilization_factor(ts), 1);
	return load_periodic_server(Qs, Ts);
}

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps){
	unsigned int testing_set[MAX_SCHEDULING_POINTS];
	int i, n_testing_set;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0)
		for (i = 0; i < n_testing_set; i++)
			if (dbf(ts, testing_set[i]) > sbf(ps, testing_set[i])) 
				return 0;

	return 1;
}
