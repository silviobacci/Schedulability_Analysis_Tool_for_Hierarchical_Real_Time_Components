#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/task_io.h>

void print_taskset(taskset *ts, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset is composed by the following tasks expressed with the (C,D,T) model:\n");

	for (i = 0; i < ts->size; i++)
		fprintf(f, "\t Task %u : (%u, %u, %u)\n", ts->tasks[i].id, ts->tasks[i].C, ts->tasks[i].D, ts->tasks[i].T);

	if(ts->is_deadline_costrained)
		fprintf(f, "Note that the taskset has the deadlines that less than or equal to the periods.\n");
	else
		fprintf(f, "Note that the taskset has the deadlines always equal to the periods.\n");

	fprintf(f, "\n");
}

void print_periodic_server(periodic_server *ps, FILE *f) {
	fprintf(f, "The periodic server has the following paramters: \n\t Qs = %d \n\t Ts = %d \n\n", ps->Qs, ps->Ts);
}

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
