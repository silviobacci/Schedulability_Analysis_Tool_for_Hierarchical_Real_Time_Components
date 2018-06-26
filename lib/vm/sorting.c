#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>
#include <vm/vm_io.h>
#include <vm/sorting.h>

void sort_cpus_by_id(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].id > v->cpus[j + 1].id) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_empty_space(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u < v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_empty_space(vm *v) {
	unsigned int i, j, n_cpus = 0;
	cpu * temp = malloc(sizeof(cpu));

	sort_by_increasing_empty_space(v);

	for (i = 0; i < v->n_cpus; i++)
		if(v->cpus[i].u > 0)
			n_cpus++;

	if(n_cpus == 0)
		n_cpus++;
	
	for (i = n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u > v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}
