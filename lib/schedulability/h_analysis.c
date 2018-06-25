#include <utilities/utilities.h>
#include <task/task_io.h>
#include <task/testing_set.h>
#include <schedulability/sbf.h>
#include <schedulability/dbf.h>

#include <schedulability/h_analysis.h>

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

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps){
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int i, n_testing_set;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0)
		for (i = 0; i < n_testing_set; i++)
			if (dbf(ts, testing_set[i]) > sbf(ps, testing_set[i])) 
				return 0;
	
	return 1;
}

periodic_server * find_periodic_server(taskset *ts, s_algorithm a) {
	unsigned int start_Qs, end_Qs, Qs, Ts, is_schedulable;
	double temp_bandwith, max_bandwith = 0.0;
	periodic_server * temp_ps, * ps = create_empty_ps();

	printf("Ts from %d to %d\n", min_period(ts), 2 * max_period(ts));
	for(Ts = min_period(ts); Ts < 2 * max_period(ts); Ts++) {
		start_Qs = my_ceil(Ts * max_bandwith, 1);
		end_Qs = my_ceil(Ts * 0.8, 1);
		printf("Qs = from %d to %d Ts = %d\n", start_Qs, end_Qs, Ts);
		for(Qs = start_Qs; Qs <= end_Qs; Qs++) {
			temp_ps = load_periodic_server(Qs, Ts);
			temp_bandwith = (double) temp_ps->Qs / temp_ps->Ts;
			is_schedulable = (a == EDF) ? h_analysis_edf(ts, temp_ps) : h_analysis_fp(ts, temp_ps);
			if(is_schedulable && temp_bandwith > max_bandwith) {
				ps = temp_ps;
				max_bandwith = temp_bandwith;
			}
		}
	}
			
	return ps;
}
