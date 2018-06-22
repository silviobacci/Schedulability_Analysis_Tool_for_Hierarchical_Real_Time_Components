#include <stdio.h>

#include <utilities/utilities.h>
#include <task/task_io.h>
#include <task/testing_set.h>
#include <schedulability/sbf.h>
#include <schedulability/dbf.h>

#include <schedulability/h_analysis.h>

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps){
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int i, n_testing_set;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		for (i = 0; i < n_testing_set; i++)
			if (dbf(ts, testing_set[i]) > sbf(ps, testing_set[i])) 
				return 0;
	}
	
	return 1;
}

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE], i;
	int j, n_testing_set;

	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0)
			for (j = 0; j < n_testing_set; j++)
				if (workload(ts, i, testing_set[j]) <= sbf(ps, testing_set[j])) 
					return 1;

	return 0;
}

periodic_server * find_periodic_server(taskset *ts) {
	unsigned int Ts = min_period(ts);
	unsigned int Qs = my_ceil(Ts * utilization_factor(ts), 1);
	return load_periodic_server(Qs, Ts);
}
