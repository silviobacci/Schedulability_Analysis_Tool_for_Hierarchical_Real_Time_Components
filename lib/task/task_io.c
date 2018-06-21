#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <task/task_io.h>

static void sort_by_periods(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	for (i = 0; i < (ts->size - 1); i++)
		for (j = 0; j < (ts->size - 1 - i); j++)
			if (ts->tasks[j].T > ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

static void sort_by_deadlines(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	for (i = 0; i < ts->size - 1; i++)
		for (j = 0; j < ts->size - 1 - i; j++)
			if (ts->tasks[j].D > ts->tasks[j + 1].D) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

taskset * load_taskset(FILE *f) {
	int res;
	unsigned int i = 0;
	taskset * ts = malloc(sizeof(taskset));
	
	if (ts == NULL)
		return NULL;
	
	ts->tasks = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	if (ts->tasks == NULL) {
		free(ts);
		return NULL;
	}

	while(!feof(f) && (i < MAX_NUMBER_TASKS)) {
		res = fscanf(f, "%u %u %u\n", &ts->tasks[i].C, &ts->tasks[i].D, &ts->tasks[i].T);
		if (res == 3)
			i++;
	}

	ts->size = i;
	ts->is_deadline_costrained = 0;

	for(i = 0; i < ts->size; i++)
		if(ts->tasks[i].D < ts->tasks[i].T)
			ts->is_deadline_costrained = 1;
			
	if(strcmp(DEFAULT_FP_ALGORITHM, "RM") == 0)	
		sort_by_periods(ts);
	else
		sort_by_deadlines(ts);

	return ts;
}

taskset * load_taskset_fp(FILE *f, char * algorithm) {
	taskset * ts = load_taskset(f);
			
	if(strcmp(DEFAULT_FP_ALGORITHM, "RM") == 0)	{
		if(strcmp(algorithm, "dm") == 0 || strcmp(algorithm, "DM") == 0)
			sort_by_deadlines(ts);
	}
	else {
		if(strcmp(algorithm, "rm") == 0 || strcmp(algorithm, "RM") == 0)
			sort_by_periods(ts);
	}

	return ts;
}

periodic_server * load_periodic_server(unsigned int Qs, unsigned int Ts) {
	periodic_server * ps = malloc(sizeof(periodic_server));
	
	if (ps == NULL)
		return NULL;
	
	ps->Qs = Qs;
	ps->Ts = Ts;

	return ps;
}
