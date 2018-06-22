#include <stdlib.h>
#include <stdio.h>

#include <utilities/utilities.h>
#include <task/task_io.h>
#include <vm/vm_io.h>

vm * load_vm(FILE *f) {
	int res;
	unsigned int Qs, Ts, i = 0;
	vm * v = malloc(sizeof(vm));
	
	if (v == NULL)
		return NULL;
	
	v->cpus = malloc(sizeof(cpu) * MAX_NUMBER_CPUS);
	
	if (v->cpus == NULL) {
		free(v);
		return NULL;
	}

	while(!feof(f) && (i < MAX_NUMBER_CPUS)) {
		v->cpus[i].algorithm = malloc(sizeof(char) * ARRAY_SIZE_ALGORITHM);
		res = fscanf(f, "%s %u %u %lf\n", v->cpus[i].algorithm, &Qs, &Ts, &v->cpus[i].max_u);
		v->cpus[i].id = i + 1;
		v->cpus[i].u = 0.0;
		v->cpus[i].ts = create_empty_ts();
		v->cpus[i].ps = load_periodic_server(Qs, Ts);
		if (res == 4)
			i++;
	}

	v->n_cpus = i;

	return v;
}
