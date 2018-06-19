#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <task/utilization_factor.h>
#include <utilities/utilities.h>
#include <h_analysis/edf.h>
#include <dbf/edf.h>
#include <sbf/sbf.h>

periodic_server * find_periodic_server_edf(taskset *ts) {
	unsigned int Ts = task_with_min_period(ts);
	unsigned int Qs = my_ceil(Ts * utilization_factor(ts), 1);
	return load_periodic_server(Qs, Ts);
}

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps){
	unsigned int sp[MAX_SCHEDULING_POINTS];
	int i, n_sp;

	n_sp = scheduling_points(ts, task_with_max_period(ts), sp, MAX_SCHEDULING_POINTS);

	if (n_sp > 0)
		for (i = 0; i < n_sp; i++)
			if (dbf_edf(ts, sp[i]) > sbf(ps->Qs, ps->Ts, sp[i])) 
				return 0;

	return 1;
}
