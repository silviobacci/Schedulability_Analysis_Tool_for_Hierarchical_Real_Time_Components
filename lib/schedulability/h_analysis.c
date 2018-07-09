//------------------------------------------------------------------------------
// H ANALYSIS:	Contains functions to perform hierarchical sched. analysis.
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "task/types.h"
#include "task/task_io.h"
#include "task/s_algorithm.h"
#include "task/testing_set.h"
#include "task/utilities.h"
#include "schedulability/sbf.h"
#include "schedulability/dbf.h"
#include "schedulability/h_analysis.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// H ANALYSIS FP: performs the sched. analysis under fp with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps) {
	unsigned int testing_set_f[MAX_TESTING_SET_SIZE], testing_set_s[MAX_TESTING_SET_SIZE], testing_set[MAX_TESTING_SET_SIZE], i;
	int j, n_testing_set, n_testing_set_f, n_testing_set_s;

	for(i = 0; i < ts->size; i++) {
		n_testing_set_f = testing_set_fp(ts, testing_set_f, i);
		n_testing_set_s = testing_set_sbf(ps, testing_set_s, testing_set_f[n_testing_set_f - 1]);

		if ((n_testing_set = merge_testing_sets(testing_set_f, n_testing_set_f, testing_set_s, n_testing_set_s, testing_set)) > 0) {
			for (j = 0; j < n_testing_set; j++)
				if(workload_function(ts, i, testing_set[j]) <= sbf(ps, testing_set[j]))
					break;
			
			if(j >= n_testing_set)
				return 0;
		}
	}

	return 1;
}

//------------------------------------------------------------------------------
// H ANALYSIS EDF: performs the sched. analysis under edf with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps){
	unsigned int testing_set_e[MAX_TESTING_SET_SIZE], testing_set_s[MAX_TESTING_SET_SIZE], testing_set[MAX_TESTING_SET_SIZE];
	int i, n_testing_set, n_testing_set_e, n_testing_set_s;
	
	n_testing_set_e = testing_set_edf(ts, testing_set_e);
	n_testing_set_s = testing_set_sbf(ps, testing_set_s, testing_set_e[n_testing_set_e - 1]);

	if ((n_testing_set = merge_testing_sets(testing_set_e, n_testing_set_e, testing_set_s, n_testing_set_s, testing_set)) > 0) 
		for (i = 0; i < n_testing_set; i++)
			if (processor_demand_function(ts, testing_set[i]) > sbf(ps, testing_set[i])) 
				return 0;
	
	return 1;
}

//------------------------------------------------------------------------------
// FIND PERIODIC SERVER: returns the server with min bandwidth able to schedule
//------------------------------------------------------------------------------

periodic_server * find_periodic_server(taskset *ts, s_algorithm a) {
	unsigned int start_Qs, end_Qs, Qs, start_Ts, end_Ts, Ts, is_schedulable;
	double temp_bandwith, best_bandwith = 1.0;
	periodic_server * temp_ps = create_empty_ps(), * ps = create_empty_ps();

	start_Ts = min_period(ts);
	end_Ts = 2 * max_period(ts);
	for(Ts = start_Ts; Ts <= end_Ts; Ts++) {
		start_Qs = (unsigned int) ceil((double) Ts * utilization_factor(ts));
		end_Qs = (unsigned int) ceil((double) Ts * best_bandwith);
		for(Qs = start_Qs; Qs <= end_Qs; Qs++) {
			temp_ps = load_periodic_server(Qs, Ts);
			temp_bandwith = (double) temp_ps->Qs / temp_ps->Ts;
			is_schedulable = (a == EDF) ? h_analysis_edf(ts, temp_ps) : h_analysis_fp(ts, temp_ps);
			
			if(is_schedulable && temp_bandwith <= best_bandwith) {
				free(ps);	
				ps = temp_ps;
				best_bandwith = temp_bandwith;
			}
			else
				free(temp_ps);
		}
	}

	if(ps->Qs != 0 && ps->Ts != 0)
		return ps;
	
	free(ps);	
	return NULL;
}
