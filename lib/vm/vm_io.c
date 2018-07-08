//------------------------------------------------------------------------------
// VM_IO:	Contains the function to load and print vm.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "vm/types.h"
#include "vm/vm_io.h"
#include "vm/sorting.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT VM: prints info about the vm
//------------------------------------------------------------------------------

void print_vm(vm *v, FILE *f) {
	unsigned int i;

	sort_cpus_by_id(v);
	fprintf(f, "The vm is composed by the following %d cpus:\n", v->n_cpus);

	for (i = 0; i < v->n_cpus; i++)
		fprintf(f, "\t Cpu %u :\n\t\t Periodic Server : (Qs = %d,  Ts = %d)\n\t\t U : %f\n\t\t MAX U : %f\n\n", v->cpus[i].id, v->cpus[i].ps->Qs, v->cpus[i].ps->Ts, v->cpus[i].u, v->cpus[i].max_u);
}

//------------------------------------------------------------------------------
// PRINT VM LOAD: prints info about the taskset allocated to the vm
//------------------------------------------------------------------------------

void print_vm_load(vm *v, FILE *f) {
	unsigned int i, j, k, round_u;

	fprintf(f, "The computational load on the vm is the following:\n");
	sort_cpus_by_id(v);
	
	for (i = 0; i < v->n_cpus; i++) {
		fprintf(f, "\t Cpu %u :\n\t\t U : %f", v->cpus[i].id, v->cpus[i].u);
		for (j = 0; j < v->cpus[i].ts->size; j++)
			fprintf(f, "\n\t\t Task %u : (%u, %u, %u)", v->cpus[i].ts->tasks[j].id, v->cpus[i].ts->tasks[j].C, v->cpus[i].ts->tasks[j].D, v->cpus[i].ts->tasks[j].T);
		fprintf(f, "\n");
	}
	
	fprintf(f, "\n");
	
	for (i = 0; i < v->n_cpus; i++) {
		fprintf(f, "\t Cpu %u : [", v->cpus[i].id);
		for (j = 0; j < v->cpus[i].ts->size; j++) {
			round_u = v->cpus[i].ts->tasks[j].C;
			for (k = 0; k < round_u; k++)
				fprintf(f, "%u",v->cpus[i].ts->tasks[j].id);
		}
		fprintf(f, "]\n");
	}
	
	fprintf(f, "\n");
}

//------------------------------------------------------------------------------
// CREATE EMPTY VM: allocate the memoery for an empty vm
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// LOAD VM: load the vm from the given file
//------------------------------------------------------------------------------

vm * load_vm(FILE *f, int ps_present) {
	unsigned int Qs = 0, Ts = 0, i = 0;
	vm * v = create_empty_vm();
	int ret;

	while(!feof(f) && i < MAX_NUMBER_CPUS) {
		if(ps_present) {
			ret = fscanf(f, "%lf %u %u\n", &v->cpus[i].max_u, &Qs, &Ts);
			v->cpus[i].ps = load_periodic_server(Qs, Ts);
			v->ps_set = 1;
		}
		else {
			ret = fscanf(f, "%lf\n", &v->cpus[i].max_u);
			v->cpus[i].ps = create_empty_ps();
			v->ps_set = 0;
		}
		v->cpus[i].id = i + 1;
		v->cpus[i].u = 0.0;
		v->cpus[i].ts = create_empty_ts();
		if((ps_present && ret == 3) || (!ps_present && ret == 1))
		i++;
	}

	v->n_cpus = i;

	return v;
}

//------------------------------------------------------------------------------
// IS PS IN FILE: return 1 if a server is specified in the file, 0 otherwise
//------------------------------------------------------------------------------

int is_ps_in_file(FILE *f, char * filename) {
	unsigned int ret = 0, tmp2, tmp3;
	double tmp1;
	
	if(fscanf(f, "%lf %u %u\n", &tmp1, &tmp2, &tmp3) == 3)
		ret = 1;
		
	fclose(f);
	
	if ((f = fopen(filename, "r")) == NULL)
		return -1;
	
	return ret;
}
