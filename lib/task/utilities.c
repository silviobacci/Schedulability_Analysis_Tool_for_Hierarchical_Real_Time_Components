#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/utilities.h>

void print_s_algorithm(s_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked under %s.\n\n", s_algorithm_to_string(a));
}

char * s_algorithm_to_string(s_algorithm a) {
	char * ret = malloc(sizeof(char) * 5);
	switch(a) {
		case FP:
			ret = "FP";
			break;
		case RM:
			ret = "RM";
			break;
		case DM:
			ret = "DM";
			break;
		case EDF:
			ret = "EDF";
			break;
	}
	
	return ret;
}

double utilization_factor_i(taskset *ts, unsigned int task_index) {
	return (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
}

double utilization_factor(taskset *ts) {
	unsigned int i;
	double U = 0;

	for(i = 0; i < ts->size; i++)
		U += (double) utilization_factor_i(ts, i);
	
	return U;
}

unsigned int max_deadline(taskset *ts) {
	unsigned int i, MAX = ts->tasks[0].D;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].D > MAX)
			MAX = ts->tasks[i].D;
	
	return MAX;
}

unsigned int max_period(taskset *ts) {
	unsigned int i, MAX = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].T > MAX)
			MAX = ts->tasks[i].T;
	
	return MAX;
}

unsigned int min_deadline(taskset *ts) {
	unsigned int i, MIN = ts->tasks[0].D;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].D < MIN)
			MIN = ts->tasks[i].D;
	
	return MIN;
}


unsigned int min_period(taskset *ts) {
	unsigned int i, MIN = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].T < MIN)
			MIN = ts->tasks[i].T;
	
	return MIN;
}

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
