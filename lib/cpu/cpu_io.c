#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <cpu/cpu_io.h>

#define ARRAY_SIZE_ALGORITHM	5

static taskset * create_empty_ts() {
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

cpu * load_cpu(FILE *f) {
	int res;
	unsigned int Qs, Ts, i = 0;
	cpu * c = malloc(sizeof(cpu));
	
	if (c == NULL)
		return NULL;
	
	c->cores = malloc(sizeof(core) * MAX_NUMBER_CORES);
	
	if (c->cores == NULL) {
		free(c);
		return NULL;
	}

	while(!feof(f) && (i < MAX_NUMBER_CORES)) {
		c->cores[i].algorithm = malloc(sizeof(char) * ARRAY_SIZE_ALGORITHM);
		res = fscanf(f, "%s %u %u\n", c->cores[i].algorithm, &Qs, &Ts);
		c->cores[i].id = i + 1;
		c->cores[i].u = 0.0;
		c->cores[i].ts = create_empty_ts();
		c->cores[i].ps = load_periodic_server(Qs, Ts);
		if (res == 3)
			i++;
	}

	c->n_cores = i;

	return c;
}
