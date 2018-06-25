#include <stdlib.h>
#include <stdio.h>

#include <utilities/utilities.h>
#include <task/task_io.h>
#include <vm/vm_io.h>

vm * create_empty_vm() {
	vm * v = malloc(sizeof(vm));
	
	if (v == NULL)
		return NULL;
	
	v->cpus = malloc(sizeof(cpu) * MAX_NUMBER_CPUS);
	
	if (v->cpus == NULL) {
		free(v);
		return NULL;
	}

	return v;
}

vm * load_vm(FILE *f) {
	int res;
	unsigned int Qs, Ts, i = 0;
	vm * v = create_empty_vm();

	while(!feof(f) && (i < MAX_NUMBER_CPUS)) {
		res = fscanf(f, "%u %u %lf\n", &Qs, &Ts, &v->cpus[i].max_u);
		v->cpus[i].id = i + 1;
		v->cpus[i].u = 0.0;
		v->cpus[i].ts = create_empty_ts();
		v->cpus[i].ps = load_periodic_server(Qs, Ts);
		if (res == 3)
			i++;
	}

	v->n_cpus = i;

	return v;
}
