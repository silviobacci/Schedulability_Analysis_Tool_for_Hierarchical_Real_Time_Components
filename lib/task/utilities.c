//------------------------------------------------------------------------------
// UTILITIES:	Contains useful functions to compute paramters of a taskset.
//------------------------------------------------------------------------------

#include "task/types.h"
#include "task/testing_set.h"
#include "task/utilities.h"
#include "schedulability/dbf.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UTILIZATION FACTOR I: utilization factor of a task
//------------------------------------------------------------------------------

double utilization_factor_i(taskset *ts, unsigned int task_index) {
	return (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
}

//------------------------------------------------------------------------------
// UTILIZATION FACTOR: utilization factor of a taskset
//------------------------------------------------------------------------------

double utilization_factor(taskset *ts) {
	unsigned int i;
	double U = 0;

	for(i = 0; i < ts->size; i++)
		U += (double) utilization_factor_i(ts, i);
	
	return U;
}

//------------------------------------------------------------------------------
// PRINT TESTING SET EDF: prints all the scheduling points for edf
//------------------------------------------------------------------------------

double utilization_factor_modified(taskset *ts) {
	unsigned int i, testing_set[MAX_TESTING_SET_SIZE];
	int j, n_testing_set;
	double MIN = 10.0, MAX = 0.0, cur_u;

	for(i = 0; i < ts->size; i++)
		if((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			for (j = 0; j < n_testing_set; j++) {
				cur_u = (double) workload_function(ts, i, testing_set[j]) / testing_set[i];
				if (cur_u < MIN) 
					MIN = cur_u;
			}

			if(MIN > MAX)
				MAX = MIN;
		}
	
	return MAX;
}

//------------------------------------------------------------------------------
// MAX DEADLINE: returns the maximum deadline among the tasks
//------------------------------------------------------------------------------

unsigned int max_deadline(taskset *ts) {
	unsigned int i, MAX = ts->tasks[0].D;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].D > MAX)
			MAX = ts->tasks[i].D;
	
	return MAX;
}

//------------------------------------------------------------------------------
// MAX PERIOD: returns the maximum period among the tasks
//------------------------------------------------------------------------------

unsigned int max_period(taskset *ts) {
	unsigned int i, MAX = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].T > MAX)
			MAX = ts->tasks[i].T;
	
	return MAX;
}

//------------------------------------------------------------------------------
// MIN DEADLINE: returns the minimum deadline among the tasks
//------------------------------------------------------------------------------

unsigned int min_deadline(taskset *ts) {
	unsigned int i, MIN = ts->tasks[0].D;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].D < MIN)
			MIN = ts->tasks[i].D;
	
	return MIN;
}

//------------------------------------------------------------------------------
// MIN PERIOD: returns the minimum period among the tasks
//------------------------------------------------------------------------------

unsigned int min_period(taskset *ts) {
	unsigned int i, MIN = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].T < MIN)
			MIN = ts->tasks[i].T;
	
	return MIN;
}

//------------------------------------------------------------------------------
// LCM: returns the hyper period of the taskset (least common multiple of all T)
//------------------------------------------------------------------------------	

static unsigned int lcm_(int a, int b){
	int lcm_temp = a;
	
	while(1){
		if(lcm_temp % b == 0 && lcm_temp % a == 0)
			break;
		lcm_temp++;
	}

	return lcm_temp;
}

unsigned int lcm(taskset *ts) {
	unsigned int i, lcm_temp = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(lcm_temp > ts->tasks[i].T)
			lcm_temp = lcm_(lcm_temp, ts->tasks[i].T);
		else
			lcm_temp = lcm_(ts->tasks[i].T, lcm_temp);

    return lcm_temp;
}
