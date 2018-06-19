#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>

#define MAX_NUMBER_TASKS 	32

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
		res = fscanf(f, "%u %u %u\n", &ts->tasks[i].C, &ts->tasks[i].D, &ts->tasks[i].P);
		if (res == 3)
			i++;
	}

	ts->size = i;

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
