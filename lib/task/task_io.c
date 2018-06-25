#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utilities/utilities.h>

#include <task/task_io.h>

taskset * create_empty_ts() {
	taskset *ts = malloc(sizeof(taskset));

	if (ts == NULL)
		return NULL;

	ts->tasks = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	if (ts->tasks == NULL) {
		free(ts);
		return NULL;
	}
	
	ts->size = 0;

	return ts;
}

periodic_server * create_empty_ps() {
	periodic_server * ps = malloc(sizeof(periodic_server));
	
	if (ps == NULL)
		return NULL;

	return ps;
}

taskset * load_taskset(FILE *f) {
	int res;
	unsigned int i = 0;
	taskset * ts = create_empty_ts();

	while(!feof(f) && (i < MAX_NUMBER_TASKS)) {
		res = fscanf(f, "%u %u %u\n", &ts->tasks[i].C, &ts->tasks[i].D, &ts->tasks[i].T);
		ts->tasks[i].id = i + 1;
		if (res == 3)
			i++;
	}

	ts->size = i;
	ts->is_deadline_costrained = 0;

	for(i = 0; i < ts->size; i++)
		if(ts->tasks[i].D < ts->tasks[i].T)
			ts->is_deadline_costrained = 1;

	return ts;
}

periodic_server * load_periodic_server(unsigned int Qs, unsigned int Ts) {
	periodic_server * ps = create_empty_ps();
	
	ps->Qs = Qs;
	ps->Ts = Ts;

	return ps;
}
