//------------------------------------------------------------------------------
// S ANALYSIS:	Contains functions to perform sched. analysis.
//------------------------------------------------------------------------------

#include "task/types.h"
#include "task/testing_set.h"
#include "task/utilities.h"
#include "schedulability/dbf.h"
#include "schedulability/s_analysis.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WORKLOAD ANALYSIS: perform the sched. analysis under fp
//------------------------------------------------------------------------------

unsigned int workload_analysis(taskset *ts) {
	unsigned int i, testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 0;
	int n_testing_set, j;
	
	for(i = 0; i < ts->size; i++) {
		is_schedulable = 0;
		if((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0)
			for (j = 0; j < n_testing_set; j++)
				if (workload_function(ts, i, testing_set[j]) <= testing_set[j])
					is_schedulable = 1;	
			
			if(!is_schedulable)
				break;
	}

	return is_schedulable;
}

//------------------------------------------------------------------------------
// PROCESSOR DEMAND ANALYSIS: perform the sched. analysis under edf
//------------------------------------------------------------------------------

unsigned int processor_demand_analysis(taskset *ts) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 1;
	int n_testing_set, i;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0)
		for (i = 0; i < n_testing_set; i++)
			if (processor_demand_function(ts, testing_set[i]) > testing_set[i])
				is_schedulable = 0;	

	return is_schedulable && utilization_factor(ts) < 1;
}
