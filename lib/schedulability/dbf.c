//------------------------------------------------------------------------------
// DBF:	Contains functions to compute the demand bound function.
//------------------------------------------------------------------------------

#include <math.h>

#include "task/types.h"
#include "schedulability/dbf.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WORKLOAD FUNTION: compute the workload function at time t for the given task
//------------------------------------------------------------------------------

unsigned int workload_function(taskset *ts, unsigned int i, unsigned int t) {
	unsigned int j, res = ts->tasks[i].C;
	
	for (j = 0; j < i; j++)
		res += (unsigned int) ceil((double) t / ts->tasks[j].T) * ts->tasks[j].C;

	return res;
}

//------------------------------------------------------------------------------
// PROCESSOR DEMAND FUNCTION: compute the processor demand function at time t
//------------------------------------------------------------------------------

double processor_demand_function(taskset *ts, unsigned int t) {
	unsigned int i, res = 0;
	
	for (i = 0; i < ts->size; i++)
		res += (unsigned int) floor((double) (t + ts->tasks[i].T - ts->tasks[i].D) / ts->tasks[i].T) * ts->tasks[i].C;

	return res;
}
