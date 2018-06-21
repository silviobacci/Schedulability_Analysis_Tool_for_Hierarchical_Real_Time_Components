#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <cpu/cpu_io.h>

#define MAX_NUMBER_CORES 	16

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
		res = fscanf(f, "%s %u %u\n", c->cores[i].algorithm, &Qs, &Ts);
		c->cores[i].ps = load_periodic_server(Qs, Ts);
		if (res == 3)
			i++;
	}

	c->n_cores = i;

	return c;
}
