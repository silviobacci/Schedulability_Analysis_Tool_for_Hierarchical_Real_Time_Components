#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utilities/utilities.h>
#include <utilities/prints.h>
#include <schedulability/h_analysis.h>

#include <schedulability/mcpu_analysis.h>

static taskset *temp_taskset(taskset *previous_ts, task to_add) {
	unsigned int i = 0;

	taskset * new_ts = malloc(sizeof(taskset));

	if (new_ts == NULL)
		return NULL;

	new_ts->tasks = malloc(sizeof(task) * (previous_ts->size + 1));

	if (new_ts->tasks == NULL) {
		free(new_ts);
		return NULL;
	}

	for(i = 0; i < previous_ts->size; i++)
		new_ts->tasks[i] = previous_ts->tasks[i];
	new_ts->tasks[i] = to_add;
	
	new_ts->size = i + 1;
	new_ts->is_deadline_costrained = 0;

	for(i = 0; i < new_ts->size; i++)
		if(new_ts->tasks[i].D < new_ts->tasks[i].T)
			new_ts->is_deadline_costrained = 1;
	
	return new_ts;
}

static taskset *create_taskset(taskset *previous_ts, task to_add) {
	taskset *new_ts = temp_taskset(previous_ts, to_add);
	free(previous_ts);
	return new_ts;
}

unsigned int schedulable(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index) {
	double u = (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	double expected_u = (double) u + v->cpus[cpu_index].u;
	if(expected_u > v->cpus[cpu_index].max_u)
		return 0;
		
	taskset * temp = temp_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);

	if(strcmp(v->cpus[cpu_index].algorithm, "RM") == 0 || strcmp(v->cpus[cpu_index].algorithm, "rm") == 0)
		return h_analysis_fp(temp, v->cpus[cpu_index].ps);
		
	if(strcmp(v->cpus[cpu_index].algorithm, "RM") == 0 || strcmp(v->cpus[cpu_index].algorithm, "rm") == 0)
		return h_analysis_fp(temp, v->cpus[cpu_index].ps);
		
	if(strcmp(v->cpus[cpu_index].algorithm, "EDF") == 0 || strcmp(v->cpus[cpu_index].algorithm, "edf") == 0)
		return h_analysis_edf(temp, v->cpus[cpu_index].ps);

	free(temp);
		
	return 0;
}

void allocate_vm(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index) {
	v->cpus[cpu_index].u += (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	v->cpus[cpu_index].ts = create_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);
}
