#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>
#include <h_analysis/edf.h>
#include <h_analysis/fp.h>

static taskset *temp_taskset(taskset *previous_ts, task to_add) {
	unsigned int i = 0;
	taskset * new_ts = malloc(sizeof(taskset));
	
	if (new_ts == NULL)
		return NULL;
	
	new_ts->tasks = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	if (new_ts->tasks == NULL) {
		free(new_ts);
		return NULL;
	}

	for(i = 0; i < previous_ts->size; i++)
		new_ts->tasks[i] = previous_ts->tasks[i];		
	new_ts->tasks[i + 1] = to_add;
	
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

unsigned int schedulable(taskset *ts, unsigned int task_index, cpu *c, unsigned int core_index) {
	if((double) ts->tasks[task_index].C / ts->tasks[task_index].T + c->cores[core_index].u > MAX_USAGE_COMPONENT)
		return 0;
		
	taskset * temp = temp_taskset(c->cores[core_index].ts, ts->tasks[task_index]);
		
	if(strcmp(c->cores[core_index].algorithm, "RM") == 0 || strcmp(c->cores[core_index].algorithm, "rm") == 0)
		h_analysis_fp(temp, c->cores[core_index].ps);
		
	if(strcmp(c->cores[core_index].algorithm, "RM") == 0 || strcmp(c->cores[core_index].algorithm, "rm") == 0)
		h_analysis_fp(temp, c->cores[core_index].ps);
		
	if(strcmp(c->cores[core_index].algorithm, "EDF") == 0 || strcmp(c->cores[core_index].algorithm, "edf") == 0)
		h_analysis_edf(temp, c->cores[core_index].ps);
		
	free(temp);
		
	return 0;
}

void allocate_cpu(taskset *ts, unsigned int task_index, cpu *c, unsigned int core_index) {
	c->cores[core_index].u += (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	c->cores[core_index].ts = create_taskset(c->cores[core_index].ts, ts->tasks[task_index]);
}
