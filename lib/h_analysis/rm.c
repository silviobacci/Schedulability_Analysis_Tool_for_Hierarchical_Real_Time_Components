#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <task/utilization_factor.h>
#include <utilities/utilities.h>
#include <h_analysis/rm.h>
#include <dbf/rm.h>
#include <sbf/sbf.h>

periodic_server * find_periodic_server_rm(taskset *ts) {
	unsigned int Ts = task_with_min_period(ts);
	printf("\n\n U = %f\n\n",  utilization_factor(ts));
	unsigned int Qs = my_ceil(Ts * utilization_factor(ts), 1);
	return load_periodic_server(Qs, Ts);
}

unsigned int h_analysis_rm(taskset *ts, periodic_server *ps) {
	unsigned int sp[MAX_SCHEDULING_POINTS], i;
	int j, n_sp;

	for(i = 0; i < ts->size; i++) {
		n_sp = scheduling_points(ts, i, sp, MAX_SCHEDULING_POINTS);
		
		if (n_sp > 0)
			for (j = 0; j < n_sp; j++)
				if (dbf_rm(ts, i, sp[j]) <= sbf(ps->Qs, ps->Ts, sp[j])) 
					return 1;
	}

	return 0;
}
